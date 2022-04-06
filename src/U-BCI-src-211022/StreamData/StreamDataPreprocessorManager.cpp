#include "StreamDataPreprocessorManager.h"

// Start the thread and the stream data preprocess
StreamDataPreprocessorManager::StreamDataPreprocessorManager(StreamDataSettings *streamDataSettings,
                                                             std::queue<StreamData *> &streamDataQueue,
                                                             StreamDataChartWindow *streamDataChartWindow,
                                                             OnlineProcessingModuleManager *onlineProcessingModuleManager,
                                                             std::atomic<bool> *shutdown,
                                                             MainWindow *mainWindow)
{
    // Generate the object that preprocesses the stream data
    m_dataPreprocessor = new StreamDataPreprocessor(streamDataSettings,
                                                    streamDataQueue,
                                                    streamDataChartWindow,
                                                    onlineProcessingModuleManager,
                                                    shutdown,
                                                    mainWindow);

    // Initialize the preprocess
    m_dataPreprocessor->InitializePreprocessing();

    // Generate the thread by QThread of Qt and move the preprocessed object to this thread
    m_dataPreprocessingThread = new QThread(this);
    m_dataPreprocessor->moveToThread(m_dataPreprocessingThread);

    // Set the Signal/Slot for start preprocess
    connect(m_dataPreprocessingThread, SIGNAL(started()), m_dataPreprocessor, SLOT(PreprocessStreamData()));

    // Set the destroying process of ending thread and  data preprocessing object by Signal/Slot
    connect(m_dataPreprocessingThread, SIGNAL(finished()), m_dataPreprocessingThread, SLOT(deleteLater()));
    connect(m_dataPreprocessingThread, SIGNAL(finished()), m_dataPreprocessor, SLOT(deleteLater()));

    // Start the thread
    m_dataPreprocessingThread->start();
}

StreamDataPreprocessorManager::~StreamDataPreprocessorManager()
{
    // Stop the thread
    m_dataPreprocessingThread->quit();
    m_dataPreprocessingThread->wait();
}
