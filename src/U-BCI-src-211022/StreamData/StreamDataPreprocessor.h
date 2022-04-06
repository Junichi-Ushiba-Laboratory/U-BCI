#ifndef STREAMDATAPREPROCESSOR_H
#define STREAMDATAPREPROCESSOR_H

#include "OnlineProcessingModule/OnlineProcessingModuleManager.h"
#include "StreamData.h"
#include "StreamDataChartWindow.h"
#include "StreamDataSettings.h"

#include <QObject>
#include <queue>
#include <thread>

#include "memory"

// Preprocess the stream data
class StreamDataPreprocessor : public QObject
{
    Q_OBJECT

public:
    StreamDataPreprocessor(StreamDataSettings *streamDataSettings,
                           std::queue<StreamData *> &streamDataQueue,
                           StreamDataChartWindow *streamDataChartWindow,
                           OnlineProcessingModuleManager *onlineProcessingModuleManager,
                           std::atomic<bool> *shutdown,
                           MainWindow *mainWindow);

    ~StreamDataPreprocessor();

    // Initialize the preprocess
    void InitializePreprocessing();

    // Get the setting information that is related to the stream data
    StreamDataSettings *GetStreamDataSettings() { return m_streamDataSettings; }

signals:
    // Send the preprocessed data and meta data to the receiving object
    void DataAvailable(const QString &streamDataName,
                       long dataId,
                       const std::shared_ptr<std::vector<double>> timeSeriesData,
                       const std::shared_ptr<std::vector<double>> timestampData,
                       StreamDataSettings *streamDataSettings);

    // Request to stop the recording of the streaming data to the main window when the connection error occurr
    void RequestRecordingStop(QString title, QString message);

public slots:
    // Set the Signal/Slot that sends the preprocessed data to the online process module
    void ConnectToOnlineProcessingModule(OnlineProcessingModule *onlineProcessingModule);

    // Preprocess the stream data and send the data to the receiving object
    void PreprocessStreamData();

private:
    // Settings information that is related to the stream data
    StreamDataSettings *m_streamDataSettings;

    // Waitinig array to receive the stream data
    std::queue<StreamData *> &m_streamDataQueue;

    // Stop flag of stream data process
    std::atomic<bool> *m_shutdown;

    // Enum that indicates the script language
    UbciScriptLanguage m_scriptLanguage;

    // Object that processes by MATLAB
    MatlabInterface *m_matlab;

    // Data ID number that were preprocessed
    long m_dataId;
};

#endif // STREAMDATAPREPROCESSOR_H
