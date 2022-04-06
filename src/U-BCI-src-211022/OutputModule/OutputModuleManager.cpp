#include "OutputModuleManager.h"

// Start the data output
OutputModuleManager::OutputModuleManager(ApplicationSettings *applicationSettings,
                                         MainWindow *mainWindow) : m_niDaqOutputModule(nullptr),
                                                                   m_niDaqOutputThread(nullptr),
                                                                   m_udpOutputModule(nullptr),
                                                                   m_httpOutputModule(nullptr)
{
    // Start the necessary data output module
    for (auto itr = applicationSettings->GetOnlineProcessingModuleSettingsMap().begin();
         itr != applicationSettings->GetOnlineProcessingModuleSettingsMap().end(); itr++)
    {
        if (itr->second != nullptr)
        {
            UbciOutputModuleType outputModuleType = itr->second->GetOutputModuleType();
            if (outputModuleType == UbciOutputModuleType::Nidaq && m_niDaqOutputModule == nullptr)
            {
                // Start the data output module that uses the NI-DAQ device
                LaunchNiDaqOutputModule();
            }
            else if (outputModuleType == UbciOutputModuleType::Udp && m_udpOutputModule == nullptr)
            {
                // Start the data output module that uses the UDP protocol
                LaunchUdpOutputModule(applicationSettings->GetOutputModuleSettings());
            }
            else if (outputModuleType == UbciOutputModuleType::Http && m_httpOutputModule == nullptr)
            {
                // Start the data output module that uses the HTTP protocol
                LaunchHttpOutputModule(applicationSettings->GetOutputModuleSettings()->GetHttpServerUrl(),
                                       applicationSettings->GetOutputModuleSettings()->GetHttpGetParameterKey(),
                                       mainWindow);
            }
        }
    }
}

OutputModuleManager::~OutputModuleManager()
{
    // Stop the thread that output the data by NI-DAQ device
    if (m_niDaqOutputThread != nullptr)
    {
        m_niDaqOutputThread->quit();
        m_niDaqOutputThread->wait();
    }

    if (m_udpOutputModule != nullptr)
        delete m_udpOutputModule;

    if (m_httpOutputModule != nullptr)
        delete m_httpOutputModule;
}

// Start the data output module that uses the NI-DAQ device
void OutputModuleManager::LaunchNiDaqOutputModule()
{
    // Not yet completed
}

// Start the data output module that uses the UDP protocol
void OutputModuleManager::LaunchUdpOutputModule(OutputModuleSettings *outputModuleSettings)
{
    // Generate the object that uses the UDP protocol
    m_udpOutputModule = new UdpOutputModule(outputModuleSettings);
}

// Start the data output module that uses the HTTP protocol
void OutputModuleManager::LaunchHttpOutputModule(const QUrl &serverUrl,
                                                 const QString &getParameterKey,
                                                 MainWindow *mainWindow)
{
    // Generate the object that does HTTP connection
    m_httpOutputModule = new HttpOutputModule(serverUrl, getParameterKey, mainWindow);
}
