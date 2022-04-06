#include "StreamDataPreprocessor.h"

#include <QElapsedTimer>

StreamDataPreprocessor::StreamDataPreprocessor(StreamDataSettings *streamDataSettings,
                                               std::queue<StreamData *> &streamDataQueue,
                                               StreamDataChartWindow *streamDataChartWindow,
                                               OnlineProcessingModuleManager *onlineProcessingModuleManager,
                                               std::atomic<bool> *shutdown,
                                               MainWindow *mainWindow) : m_streamDataSettings(streamDataSettings),
                                                                         m_streamDataQueue(streamDataQueue),
                                                                         m_shutdown(shutdown),
                                                                         m_matlab(nullptr),
                                                                         m_dataId(0)
{
    // Register the data type of result data that sends by Signal / Slot
    qRegisterMetaType<std::shared_ptr<std::vector<double>>>("std::shared_ptr<std::vector<double>>");

    // Set the Signal/Slot that sends the preprocessed data to the main window
    if (streamDataSettings->IsChartDisplayed())
        connect(this, &StreamDataPreprocessor::DataAvailable,
                streamDataChartWindow, &StreamDataChartWindow::ShowDataInChart);

    // Set the Signal/Slot that sends the preprocessed data when the stream data includes each online process module
    for (auto itr = onlineProcessingModuleManager->GetOnlineProcessingModuleMap().begin();
         itr != onlineProcessingModuleManager->GetOnlineProcessingModuleMap().end(); itr++)
    {
        if (itr->second->GetOnlineProcessingModuleSettings()->GetInputStreamDataNameList().contains(streamDataSettings->GetStreamDataName()))
            ConnectToOnlineProcessingModule(itr->second);
    }

    // Set Signal / Slot that stops the program when connection error occurr
    connect(this, &StreamDataPreprocessor::RequestRecordingStop, mainWindow, &MainWindow::StopRecording);

    qInfo() << m_streamDataSettings->GetStreamDataName() << ": Data preprocessor launched.";
}

StreamDataPreprocessor::~StreamDataPreprocessor()
{
    if (m_matlab != nullptr)
        delete m_matlab;

    qInfo() << m_streamDataSettings->GetStreamDataName() << ": Data preprocessor closed.";
}

// Initialize the preprocess
void StreamDataPreprocessor::InitializePreprocessing()
{
    // Get the enum that show the language of process script
    m_scriptLanguage = m_streamDataSettings->GetScriptLanguage();

    // Start-up the execution environment responding the the script language
    if (m_scriptLanguage == UbciScriptLanguage::Matlab)
    {
        try
        {
            // Start MATLAB
            m_matlab = new MatlabInterface(m_streamDataSettings->GetPreprocessingScriptPath());

            // Initialize the user_data structure of MATLAB workspace by initialization script
            if (!m_streamDataSettings->GetInitializingScriptPath().isEmpty())
                m_matlab->InitializeUserData(m_streamDataSettings->GetInitializingScriptPath());
        }
        catch (std::exception &exception)
        {
            // Stop the program
            QString message = "MATLAB initialization failed in ";
            message += m_streamDataSettings->GetStreamDataName();
            message += ".\n";
            message += exception.what();
            emit RequestRecordingStop("MATLAB Initialization Error", message);
        }
    }
}

// Set the Signal/Slot that sends the preprocessed data to the online process module
void StreamDataPreprocessor::ConnectToOnlineProcessingModule(OnlineProcessingModule *onlineProcessingModule)
{
    // Set the Signal/Slot that sends the processed data to the receiving object
    connect(this, &StreamDataPreprocessor::DataAvailable,
            onlineProcessingModule, &OnlineProcessingModule::ReceiveStreamData);
}

// Preprocess the stream data and send the data to the receiving object
void StreamDataPreprocessor::PreprocessStreamData()
{
    while (!*m_shutdown)
    {
        if (!m_streamDataQueue.empty())
        {
            // Acquire the stream data from the waiting array
            StreamData *streamData = m_streamDataQueue.front();

            // Array that stores the preprocessed data
            std::shared_ptr<std::vector<double>> timeSeriesData = std::make_shared<std::vector<double>>();
            std::shared_ptr<std::vector<double>> timestampData = std::make_shared<std::vector<double>>();

            // For MATLAB
            if (m_scriptLanguage == UbciScriptLanguage::Matlab)
            {
                try
                {
                    // Input the stream data to the MATLAB workspace
                    m_matlab->InputStreamData(m_streamDataSettings->GetStreamDataName(),
                                              streamData->GetTimeSeriesData(),
                                              streamData->GetTimestampData(),
                                              m_streamDataSettings);

                    // Execute the MATLAB function that preprocess the stream data
                    m_matlab->ProcessData(timeSeriesData, timestampData);
                }
                catch (std::exception &exception)
                {
                    // Stop the program
                    QString message = "Processing by MATLAB failed in ";
                    message += m_streamDataSettings->GetStreamDataName();
                    message += ".\n";
                    message += exception.what();
                    emit RequestRecordingStop("MATLAB Processing Error", message);
                }
            }
            // When it does not preprocess
            else
            {
                // Give the buffer data directly
                std::copy(streamData->GetTimeSeriesData()->begin(), streamData->GetTimeSeriesData()->end(),
                          back_inserter(*timeSeriesData));
                std::copy(streamData->GetTimestampData()->begin(), streamData->GetTimestampData()->end(),
                          back_inserter(*timestampData));
            }

            // Send the preprocessed data and meta data to the receiving object
            emit DataAvailable(m_streamDataSettings->GetStreamDataName(), m_dataId++,
                               timeSeriesData, timestampData, m_streamDataSettings);

            // Delete the stream data that finished receiving and release the memory
            if (!m_streamDataQueue.empty())
                m_streamDataQueue.pop();
            delete streamData;
        }

        // Make interval time between loop
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
}
