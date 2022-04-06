#ifndef DAQSTREAMINGWRAPPER_H
#define DAQSTREAMINGWRAPPER_H

#include <QObject>

class MainWindow;

// Wrapper class for C-language source code that outputs signals of NI-DAQ device by LSL
class DaqStreaming : public QObject
{
    Q_OBJECT

public:
    DaqStreaming(MainWindow *mainWindow);

    // Get the necessary configuration information as text
    QString GetSettingsInfo();

signals:
    // Sends the error information to catch function
    void SendError(int errorCode, char *errorMessage);

public slots:
    // Output the analog signal of NI-DAQ device by LSL
    void StartDaqStreaming();

    // Stop the analog signal of NI-DAQ device by LSL
    void StopDaqStreaming();
};

#endif // DAQSTREAMINGWRAPPER_H
