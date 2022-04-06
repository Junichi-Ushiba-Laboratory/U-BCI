#include "OnlineProcessingModuleManager.h"

// Start the thread and online process
OnlineProcessingModuleManager::OnlineProcessingModuleManager(
    std::map<QString, OnlineProcessingModuleSettings *> &onlineProcessingModuleSettingsMap,
    std::map<QString, StreamDataSettings *> &streamDataSettingsMap,
    OutputModuleManager *outputModuleManager,
    MainWindow *mainWindow)
{
    for (auto itr = onlineProcessingModuleSettingsMap.begin();
         itr != onlineProcessingModuleSettingsMap.end(); itr++)
    {
        if (itr->second != nullptr)
        {
            // Generate the online processing module
            OnlineProcessingModule *onlineProcessingModule =
                new OnlineProcessingModule(itr->second, streamDataSettingsMap, mainWindow);

            // Initialize the process
            onlineProcessingModule->InitializeProcessing();

            // Set the connection to the data output module
            ConnectToOutputModule(onlineProcessingModule, itr->second->GetOutputModuleType(),
                                  outputModuleManager);

            // Register the online process module to the management map
            m_onlineProcessingModuleMap[itr->first] = onlineProcessingModule;

            // Generate the thread by the QThread of Qt and move the online processing module to this thread
            QThread *onlineProcessingrThread = new QThread(this);
            onlineProcessingModule->moveToThread(onlineProcessingrThread);

            // Register the thread that executes the online process to the management map
            m_onlineProcessingThreadMap[itr->first] = onlineProcessingrThread;

            // Set the destroying process of ending thread and  data preprocessing object by Signal/Slot
            connect(onlineProcessingrThread, SIGNAL(finished()),
                    onlineProcessingrThread, SLOT(deleteLater()));
            connect(onlineProcessingrThread, SIGNAL(finished()),
                    onlineProcessingModule, SLOT(deleteLater()));

            // Start the thread
            onlineProcessingrThread->start();
        }
    }
}

OnlineProcessingModuleManager::~OnlineProcessingModuleManager()
{
    // Stop the thread
    for (auto itr = m_onlineProcessingThreadMap.begin();
         itr != m_onlineProcessingThreadMap.end(); itr++)
    {
        itr->second->quit();
        itr->second->wait();
    }
}

// Connect to the data output module
void OnlineProcessingModuleManager::ConnectToOutputModule(OnlineProcessingModule *onlineProcessingModule,
                                                          UbciOutputModuleType outputModuleType,
                                                          OutputModuleManager *outputModuleManager)
{
    if (outputModuleType == UbciOutputModuleType::Nidaq)
        onlineProcessingModule->ConnectToNiDaqOutputModule(outputModuleManager->GetNiDaqOutputModule());
    else if (outputModuleType == UbciOutputModuleType::Udp)
        onlineProcessingModule->ConnectToUdpOutputModule(outputModuleManager->GetUdpOutputModule());
    else if (outputModuleType == UbciOutputModuleType::Http)
        onlineProcessingModule->ConnectToHttpOutputModule(outputModuleManager->GetHttpOutputModule());
    else
    { /* Do nothing*/
    }
}
