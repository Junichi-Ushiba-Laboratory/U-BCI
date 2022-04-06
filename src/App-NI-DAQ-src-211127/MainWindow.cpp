#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_streamingThread(nullptr),
      CONFIGURATION_FILE_NAME("config.cfg")
{
    ui->setupUi(this);
    this->setWindowTitle(PROGRAM_NAME + "-" + PROGRAM_VERSION);

    // Disable the screen maximization button
    setWindowFlags((windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);

    // Fix the screen size
    this->setFixedSize(357, 100);

    // Set the permission of use in start button and stop button
    ui->_startDaqBtn->setEnabled(true);
    ui->_stopDaqBtn->setEnabled(false);
    ui->_showSettingsBtn->setEnabled(true);

    // Show the configuration information of necessary program
    DaqStreaming daqStreaming(this);
    ui->_daqInfoLabel->setText(daqStreaming.GetSettingsInfo());

    // Set the Signal/Slot of signal output of NI-DAQ device that starts and stops
    connect(ui->_startDaqBtn, &QPushButton::clicked, this, &MainWindow::StartDaqStreaming);
    connect(ui->_stopDaqBtn, &QPushButton::clicked, this, &MainWindow::StopDaqStreaming);

    // Set the Signal/Slot that shows the default configuration file by text editors
    connect(ui->_showSettingsBtn, &QPushButton::clicked, this, &MainWindow::ShowSettings);

    // Set the shortcut for operation button
    QShortcut *startDaqBtnShortcut = new QShortcut(QKeySequence("S"), ui->_startDaqBtn);
    connect(startDaqBtnShortcut, &QShortcut::activated, this, &MainWindow::StartDaqStreaming);
    QShortcut *stopDaqBtnShortcut = new QShortcut(QKeySequence("T"), ui->_stopDaqBtn);
    connect(stopDaqBtnShortcut, &QShortcut::activated, this, &MainWindow::StopDaqStreaming);
    QShortcut *showSettingsShortcut = new QShortcut(QKeySequence("C"), ui->_showSettingsBtn);
    connect(showSettingsShortcut, &QShortcut::activated, this, &MainWindow::ShowSettings);

    // Set the shortcut for quitting the program
    QAction *quit = new QAction(this);
    quit->setShortcut(Qt::Key_Q | Qt::CTRL);
    connect(quit, SIGNAL(triggered()), this, SLOT(close()));
    this->addAction(quit);
}

MainWindow::~MainWindow()
{
    if (m_streamingThread != nullptr)
        StopDaqStreaming();

    delete ui;

    qInfo() << "\"App-NI-DAQ\""
            << ": Closed.";
}

// Start the thread and output the analog signal of NI-DAQ device by LSL
void MainWindow::StartDaqStreaming()
{
    // Set the permission of use in start button and stop button
    ui->_startDaqBtn->setEnabled(false);
    ui->_stopDaqBtn->setEnabled(true);
    ui->_showSettingsBtn->setEnabled(false);

    // Generate the object that outputs the signals of NI-DAQ device
    m_daqStreaming = new DaqStreaming(this);

    // Show the configuration information of necessary program
    ui->_daqInfoLabel->setText(m_daqStreaming->GetSettingsInfo());

    // Generate the thread by QThread of Qt and moves the signal output object to this thread
    m_streamingThread = new QThread(this);
    m_daqStreaming->moveToThread(m_streamingThread);

    // Set the Signal/Slot that starts the signal output
    connect(m_streamingThread, SIGNAL(started()), m_daqStreaming, SLOT(StartDaqStreaming()));

    // Set the ending thread and destroyed singal output object by Signal/Slot
    connect(m_streamingThread, SIGNAL(finished()), m_streamingThread, SLOT(deleteLater()));
    connect(m_streamingThread, SIGNAL(finished()), m_daqStreaming, SLOT(deleteLater()));

    // Start the thread
    m_streamingThread->start();
}

// Stop the analog signal of NI-DAQ device by LSL
void MainWindow::StopDaqStreaming()
{
    // Stop the signal output
    m_daqStreaming->StopDaqStreaming();

    // Stop the thread
    if (m_streamingThread != nullptr)
    {
        m_streamingThread->quit();
        m_streamingThread->wait();
        m_streamingThread = nullptr;
    }

    // Set the permission of use in start button and stop button
    ui->_startDaqBtn->setEnabled(true);
    ui->_stopDaqBtn->setEnabled(false);
    ui->_showSettingsBtn->setEnabled(true);
}

// Show the error information in the dialog
void MainWindow::ShowError(int errorCode, char *errorMessage)
{
    QString message = "Error code: " + QString::number(errorCode) + "\n" + errorMessage;
    QMessageBox::critical(this, "App-NI-DAQ Error", message);
    StopDaqStreaming();
}

// Show the default configuration file by text editor
void MainWindow::ShowSettings()
{
    // Get the path of default configuration file
    // The default configuration file is stored in the directory where the execution file exists
    QString configFilePath = QApplication::applicationDirPath() + "/" + CONFIGURATION_FILE_NAME;
    QFileInfo configFileInfo(configFilePath);
    if (!configFileInfo.exists() || !configFileInfo.isFile())
    {
        QString message = CONFIGURATION_FILE_NAME +
                          " file cannot be found in the folder where App-NI-DAQ-<yymmdd>.exe file exists.";
        QMessageBox::critical(this, "App-NI-DAQ Error", message);
        return;
    }

    // Open the configuration file by notepad
    QProcess *process = new QProcess(this);
    process->start("notepad.exe " + configFilePath);
}
