#ifndef DATATHREAD_H
#define DATATHREAD_H

#include "StreamData.h"
#include "StreamDataPreprocessor.h"
#include "OnlineProcessingModule/OnlineProcessingModuleManager.h"

#include <lsl_cpp.h>

#include <QThread>

class StreamDataPreprocessor;

// Start the thread and preprocess the stream data
class StreamDataPreprocessorManager : public QThread
{
public:
    // Start the thread and the stream data preprocess
    StreamDataPreprocessorManager(StreamDataSettings *streamDataSettings,
                                  std::queue<StreamData *> &streamDataQueue,
                                  StreamDataChartWindow *streamDataChartWindow,
                                  OnlineProcessingModuleManager *onlineProcessingModuleManager,
                                  std::atomic<bool> *shutdown,
                                  MainWindow *mainWindow);

    ~StreamDataPreprocessorManager();

private:
    // Object that preprocess the stream data
    StreamDataPreprocessor *m_dataPreprocessor;

    // Thread that executes the preprocess the stream data
    QThread *m_dataPreprocessingThread;
};

#endif // DATATHREAD_H
