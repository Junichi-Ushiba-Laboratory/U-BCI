#include "OnlineProcessingModule.h"

OnlineProcessingModule::OnlineProcessingModule(OnlineProcessingModuleSettings *moduleSettings,
                                               std::map<QString, StreamDataSettings *> &streamDataSettingsMap,
                                               MainWindow *mainWindow) : m_moduleSettings(moduleSettings),
                                                                         m_isFirstStreamData(true),
                                                                         m_streamDataSettingstMap(streamDataSettingsMap),
                                                                         m_lastSynchronizedTime(0),
                                                                         m_matlab(nullptr)
{
    // Initialize the array that holds the buffer of stream data and synchronized data
    for (int i = 0; i < moduleSettings->GetInputStreamDataNameList().size(); i++)
    {
        // Get the name of stream data
        QString streamDataName = moduleSettings->GetInputStreamDataNameList().at(i);

        // Initialize the array that holds the buffer of time-series data and synchronized data
        m_timeSeriesDataBuffer.insert(std::pair<QString, std::queue<double>>(streamDataName, std::queue<double>()));
        m_synchronizedTimeSeriesData.insert(std::pair<QString, std::vector<double>>(streamDataName, std::vector<double>()));

        // Initialize the array that holds the buffer of time data and synchronized data
        m_timestampDataBuffer.insert(std::pair<QString, std::queue<double>>(streamDataName, std::queue<double>()));
        m_synchronizedTimestampData.insert(std::pair<QString, std::vector<double>>(streamDataName, std::vector<double>()));
    }

    // Register the data type of result data that sends by Signal / Slot
    qRegisterMetaType<std::shared_ptr<std::vector<double>>>("std::shared_ptr<std::vector<double>>");

    // Set Signal / Slot that stops the program when connection error occurr
    connect(this, &OnlineProcessingModule::RequestRecordingStop, mainWindow, &MainWindow::StopRecording);

    qInfo() << moduleSettings->GetModuleName() << ": Launched.";
}

OnlineProcessingModule::~OnlineProcessingModule()
{
    if (m_matlab != nullptr)
        delete m_matlab;

    qInfo() << m_moduleSettings->GetModuleName() << ": Closed.";
}

// Initialize the process
void OnlineProcessingModule::InitializeProcessing()
{
    // Get the enum that show the language of process script
    m_scriptLanguage = m_moduleSettings->GetScriptLanguage();

    // Start-up the execution environment responding the the script language
    if (m_scriptLanguage == UbciScriptLanguage::Matlab)
    {
        try
        {
            // Start MATLAB
            m_matlab = new MatlabInterface(m_moduleSettings->GetProcessingScriptPath());

            // Initialize the user_data structure of MATLAB workspace by initialization script
            if (!m_moduleSettings->GetInitializingScriptPath().isEmpty())
                m_matlab->InitializeUserData(m_moduleSettings->GetInitializingScriptPath());
        }
        catch (std::exception &exception)
        {
            // Stop the program
            QString message = "MATLAB initialization failed in ";
            message += m_moduleSettings->GetModuleName();
            message += ".\n";
            message += exception.what();
            emit RequestRecordingStop("MATLAB Initialization Error", message);
        }
    }
}

// Connect to the data output module by NI-DAQ
void OnlineProcessingModule::ConnectToNiDaqOutputModule(NiDaqOutputModule *niDaqOutputModule)
{
    connect(this, &OnlineProcessingModule::DataAvailable,
            niDaqOutputModule, &NiDaqOutputModule::OutputData);
}

// Connect to the data output module by UDP connection
void OnlineProcessingModule::ConnectToUdpOutputModule(UdpOutputModule *udpOutputModule)
{
    connect(this, &OnlineProcessingModule::DataAvailable,
            udpOutputModule, &UdpOutputModule::OutputData);
}

// Connect to the data output module by HTTP connection
void OnlineProcessingModule::ConnectToHttpOutputModule(HttpOutputModule *httpOutputModule)
{
    connect(this, &OnlineProcessingModule::DataAvailable,
            httpOutputModule, &HttpOutputModule::OutputData);
}

// Receive the stream data
// Start the process using the data if there are parts that synchronize between stream data
void OnlineProcessingModule::ReceiveStreamData(
    const QString &streamDataName,
    long dataId,
    const std::shared_ptr<std::vector<double>> timeSeriesData,
    const std::shared_ptr<std::vector<double>> timestampData,
    StreamDataSettings *streamDataSettings)
{
    // Initialize when the first stream data has been received
    if (m_isFirstStreamData)
    {
        // Initialize the time when the synchronization is stable
        m_lastSynchronizedTime = timestampData->front();

        m_isFirstStreamData = false;
    }

    // Store the receiving time-series data to the buffer
    for (int i = 0; i < timeSeriesData->size(); i++)
        m_timeSeriesDataBuffer[streamDataName].push(timeSeriesData->data()[i]);

    // Store the receiving time-series data and time data to the buffer
    for (int i = 0; i < timestampData->size(); i++)
        m_timestampDataBuffer[streamDataName].push(timestampData->data()[i]);

    // Acquire the synchronized stream data
    bool isSynchronized = GetSynchronizedStreamData(m_timeSeriesDataBuffer,
                                                    m_timestampDataBuffer,
                                                    m_synchronizedTimeSeriesData,
                                                    m_synchronizedTimestampData);

    // Process the synchronized stream data
    if (isSynchronized)
    {
        ProcessStreamData(m_synchronizedTimeSeriesData, m_synchronizedTimestampData, m_streamDataSettingstMap);
    }
    // Empty the buffer when it is unavailable to receive the synchronized data
    else
    {
        if (timestampData->front() - m_lastSynchronizedTime > BUFFRING_TIMEOUT)
        {
            for (auto itr = m_timestampDataBuffer.begin(); itr != m_timestampDataBuffer.end(); itr++)
            {
                while (!m_timeSeriesDataBuffer[itr->first].empty())
                    m_timeSeriesDataBuffer[itr->first].pop();
                while (!m_timestampDataBuffer[itr->first].empty())
                    m_timestampDataBuffer[itr->first].pop();
            }
        }
    }
}

// Get the data by putting tht synchronized data as argument
// Return true when it acquired synchronized data
bool OnlineProcessingModule::GetSynchronizedStreamData(
    std::map<QString, std::queue<double>> &timeSeriesDataBuffer,
    std::map<QString, std::queue<double>> &timestampDataBuffer,
    std::map<QString, std::vector<double>> &synchronizedTimeSeriesData,
    std::map<QString, std::vector<double>> &synchronizedTimestampData)
{
    // Flag that shows whether there is the synchronized stream data
    bool isSynchronized = true;

    // Get the latest start time and fastest end time between the stream data
    double startTime = -1.0;
    double endTime = DBL_MAX;
    for (auto itr = timestampDataBuffer.begin(); itr != timestampDataBuffer.end(); itr++)
    {
        if (itr->second.size() == 0)
        {
            isSynchronized = false;
            break;
        }
        if (itr->second.front() > startTime)
            startTime = itr->second.front();
        if (itr->second.back() < endTime)
            endTime = itr->second.back();
    }

    // Judges whether there is synchronized stream data
    if (startTime > endTime)
        isSynchronized = false;

    // Acquire the synchronized data
    if (isSynchronized)
    {
        for (auto itr = timestampDataBuffer.begin(); itr != timestampDataBuffer.end(); itr++)
        {
            // Empty the array that holds the synchronized data
            synchronizedTimeSeriesData[itr->first].clear();
            synchronizedTimestampData[itr->first].clear();

            int usedChannelCount = m_streamDataSettingstMap[itr->first]->GetUsedChannelCount();
            while (!itr->second.empty() && itr->second.front() <= endTime)
            {
                if (itr->second.front() >= startTime)
                {
                    // Acquire time-series data
                    for (int ch = 0; ch < usedChannelCount; ch++)
                    {
                        synchronizedTimeSeriesData[itr->first].emplace_back(
                            timeSeriesDataBuffer[itr->first].front());
                        timeSeriesDataBuffer[itr->first].pop();
                    }

                    // Acquire the time data
                    synchronizedTimestampData[itr->first].emplace_back(itr->second.front());
                    itr->second.pop();
                }
                else
                {
                    // Only delete the component of each buffer
                    itr->second.pop();
                    for (int ch = 0; ch < usedChannelCount; ch++)
                        timeSeriesDataBuffer[itr->first].pop();
                }
            }
        }

        // Update the synchronized time
        m_lastSynchronizedTime = endTime;
    }

    return isSynchronized;
}

// Process the stream data
void OnlineProcessingModule::ProcessStreamData(
    std::map<QString, std::vector<double>> &timeSeriesData,
    std::map<QString, std::vector<double>> &timestampData,
    std::map<QString, StreamDataSettings *> &streamDataSettingsMap)
{
    // Generate the array that stores the result data
    std::shared_ptr<std::vector<double>> resultsData = std::make_shared<std::vector<double>>();

    // Execute the process script
    if (m_scriptLanguage == UbciScriptLanguage::Matlab)
    {
        try
        {
            // Input the stream data to the MATLAB workspace
            m_matlab->InputStreamData(timeSeriesData, timestampData, streamDataSettingsMap);

            // Execute the MATLAB function that processes the stream data
            m_matlab->ProcessData(resultsData);
        }
        catch (std::exception &exception)
        {
            // Stop the program
            QString message = "Processing by MATLAB failed in ";
            message += m_moduleSettings->GetModuleName();
            message += ".\n";
            message += exception.what();
            emit RequestRecordingStop("MATLAB Processing Error", message);
        }
    }

    // Send the result data to the output module
    if (!resultsData->empty())
        emit DataAvailable(m_moduleSettings->GetModuleName(), resultsData);
}
