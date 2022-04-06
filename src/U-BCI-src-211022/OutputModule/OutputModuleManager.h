#ifndef OUTPUTMODULEMANAGER_H
#define OUTPUTMODULEMANAGER_H

#include "ApplicationSettings.h"
#include "HttpOutputModule.h"
#include "mainwindow.h"
#include "NiDaqOutputModule.h"
#include "OnlineProcessingModule/OnlineProcessingModuleSettings.h"
#include "UdpOutputModule.h"

#include <QThread>

// Manage the data output module
class OutputModuleManager : public QThread
{
public:
    // Start the data output
    OutputModuleManager(ApplicationSettings *applicationSettings,
                        MainWindow *mainWindows);

    ~OutputModuleManager();

    // Get the data output module that uses the NI-DAQ device
    NiDaqOutputModule *GetNiDaqOutputModule() { return m_niDaqOutputModule; }

    // Get the data output module that uses the UDP protocol
    UdpOutputModule *GetUdpOutputModule() { return m_udpOutputModule; }

    // Get the data output module that uses the HTTP protocol
    HttpOutputModule *GetHttpOutputModule() { return m_httpOutputModule; }

private:
    // Start the data output module that uses the NI-DAQ device
    void LaunchNiDaqOutputModule();

    // Start the data output module that uses the UDP protocol
    void LaunchUdpOutputModule(OutputModuleSettings *outputModuleSettings);

    // Start the data output module that uses the HTTP protocol
    void LaunchHttpOutputModule(const QUrl &serverUrl,
                                const QString &getParameterKey,
                                MainWindow *mainWindow);

private:
    // Data output module that uses the NI-DAQ device
    NiDaqOutputModule *m_niDaqOutputModule;

    // Executing thread of the data output that uses the NI-DAQ
    QThread *m_niDaqOutputThread;

    // Executing thread of the data output that uses the UDP protocol
    UdpOutputModule *m_udpOutputModule;

    // Executing thread of the data output that uses the HTTP protocol
    HttpOutputModule *m_httpOutputModule;
};

#endif // OUTPUTMODULEMANAGER_H
