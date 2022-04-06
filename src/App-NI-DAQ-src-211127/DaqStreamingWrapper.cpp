#include "DaqStreaming.h"
#include "DaqStreamingWrapper.h"
#include "MainWindow.h"

#include <QDebug>

DaqStreaming::DaqStreaming(MainWindow *mainWindow)
{
    // Set the Signal/Slot that sends error information
    connect(this, &DaqStreaming::SendError, mainWindow, &MainWindow::ShowError);
}

// Get the necessary configuration information as text
QString DaqStreaming::GetSettingsInfo()
{
    // String that stores message when error exists
    char errorMessage[4096] = {'\0'};

    // String that stores the configuration information of necessary programs
    char settingsInfo[4096] = {'\0'};

    // Get the configuration information of the program
    int errorCode = GetSettings(settingsInfo, 4096, errorMessage, 4096);

    if (errorCode != 0)
        emit SendError(errorCode, errorMessage);

    return QString(settingsInfo);
}

// Output the analog signal of NI-DAQ device by LSL
void DaqStreaming::StartDaqStreaming()
{
    qInfo() << "\"App-NI-DAQ\""
            << ": DAQ streaming ready to be started.";

    // String that stores message when error exists
    char errorMessage[4096] = {'\0'};

    // Start the signal output
    int errorCode = StartDaq(errorMessage, 4096);

    if (errorCode == -8999)
        qInfo() << "\"App-NI-DAQ\""
                << ": Stopped.";
    else if (errorCode == -8998)
    {
        strcpy_s(errorMessage, 4096,
                 "[Error] DAQ data acquisition stopped due to an error.\n");
        emit SendError(errorCode, errorMessage);
    }
    else if (errorCode != 0)
        emit SendError(errorCode, errorMessage);
    else
        qInfo() << "\"App-NI-DAQ\""
                << ": DAQ streaming stopped.";
}

// Stop the analog signal of NI-DAQ device by LSL
void DaqStreaming::StopDaqStreaming()
{
    // Stop the signal output
    StopDaq();
}
