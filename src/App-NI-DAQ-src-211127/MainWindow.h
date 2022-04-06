#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DaqStreamingWrapper.h"

#include <QFileInfo>
#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>
#include <QShortcut>
#include <QString>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

// Main display of App-NI-DAQ
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public slots:
    // Show the error information in the dialog
    void ShowError(int errorCode, char *errorMessage);

private slots:
    // Start the thread and output the analog signal of NI-DAQ device by LSL
    void StartDaqStreaming();

    // Stop the analog signal of NI-DAQ device by LSL
    void StopDaqStreaming();

    // Show the default configuration file by text editor
    void ShowSettings();

private:
    // Program name
    QString PROGRAM_NAME = "App-NI-DAQ";

    // Program version
    QString PROGRAM_VERSION = "211127";

    // Main window
    Ui::MainWindow *ui;

    // Wrapper object of C-language source code that ouput the signal of NI-DAQ device by LSL
    DaqStreaming *m_daqStreaming;

    // Thread that outputs the singal of NI-DAQ device
    QThread *m_streamingThread;

    // Default name of configuration file
    QString CONFIGURATION_FILE_NAME;
};

#endif // MAINWINDOW_H
