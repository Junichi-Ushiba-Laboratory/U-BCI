#ifndef ONLINEPROCESSINGMODULEMANAGER_H
#define ONLINEPROCESSINGMODULEMANAGER_H

#include "ApplicationSettings.h"
#include "OnlineProcessingModule.h"
#include "OutputModule/OutputModuleManager.h"
#include "StreamData/StreamData.h"

#include <QThread>

// Manage the online processing module
class OnlineProcessingModuleManager : public QThread
{
public:
    // Start the thread and online process
    OnlineProcessingModuleManager(
        std::map<QString, OnlineProcessingModuleSettings *> &onlineProcessingModuleSettingsMap,
        std::map<QString, StreamDataSettings *> &streamDataSettingsMap,
        OutputModuleManager *outputModuleManager,
        MainWindow *mainWindow);

    ~OnlineProcessingModuleManager();

    // Get every online process module
    std::map<QString, OnlineProcessingModule *> &GetOnlineProcessingModuleMap()
    {
        return m_onlineProcessingModuleMap;
    }

private:
    // Connect to the data output module
    void ConnectToOutputModule(OnlineProcessingModule *onlineProcessingModule,
                               UbciOutputModuleType outputModuleType,
                               OutputModuleManager *outputModuleManager);

    // Map that manages the online process module
    std::map<QString, OnlineProcessingModule *> m_onlineProcessingModuleMap;

    // Map that manages to execute the online process
    std::map<QString, QThread *> m_onlineProcessingThreadMap;
};

#endif // ONLINEPROCESSINGMODULEMANAGER_H
