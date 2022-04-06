#ifndef ONLINEPROCESSINGMODULE_H
#define ONLINEPROCESSINGMODULE_H

#include "ApplicationSettings.h"
#include "OutputModule/HttpOutputModule.h"
#include "MatlabInterface/MatlabInterface.h"
#include "OutputModule/NiDaqOutputModule.h"
#include "OnlineProcessingModuleSettings.h"
#include "OutputModule/UdpOutputModule.h"

#include <QObject>

#include <queue>

// Online process of stream data
class OnlineProcessingModule : public QObject
{
    Q_OBJECT

public:
    OnlineProcessingModule(OnlineProcessingModuleSettings *moduleSettings,
                           std::map<QString, StreamDataSettings *> &streamDataSettingsMap,
                           MainWindow *mainWindow);

    ~OnlineProcessingModule();

    // Initialize the process
    void InitializeProcessing();

    // Connect to the data output module by NI-DAQ
    void ConnectToNiDaqOutputModule(NiDaqOutputModule *niDaqOutputModule);

    // Connect to the data output module by UDP connection
    void ConnectToUdpOutputModule(UdpOutputModule *udpOutputModule);

    // Connect to the data output module by HTTP connection
    void ConnectToHttpOutputModule(HttpOutputModule *httpOutputModule);

    // Get the setting information of online process module
    OnlineProcessingModuleSettings *GetOnlineProcessingModuleSettings()
    {
        return m_moduleSettings;
    }

signals:
    // Send the result data to the output module
    void DataAvailable(const QString &onlineProcessingModuleName,
                       const std::shared_ptr<std::vector<double>> resultsData);

    // Request to stop the recording of the streaming data to the main window when the connection error occurr
    void RequestRecordingStop(QString title, QString message);

public slots:
    // Receive the stream data
    // Start the process using the data if there are parts that synchronize between stream data
    void ReceiveStreamData(const QString &streamDataName, long dataId,
                           const std::shared_ptr<std::vector<double>> timeSeriesData,
                           const std::shared_ptr<std::vector<double>> timestampData,
                           StreamDataSettings *streamDataSettings);

private:
    // Get the data by putting tht synchronized data as argument
    // Return true when it acquired synchronized data
    bool GetSynchronizedStreamData(std::map<QString, std::queue<double>> &timeSeriesDataBuffer,
                                   std::map<QString, std::queue<double>> &timestampDataBuffer,
                                   std::map<QString, std::vector<double>> &synchronizedTimeSeriesData,
                                   std::map<QString, std::vector<double>> &synchronizedTimestampData);

    // Process the stream data
    void ProcessStreamData(std::map<QString, std::vector<double>> &timeSeriesData,
                           std::map<QString, std::vector<double>> &timestampData,
                           std::map<QString, StreamDataSettings *> &streamDataSettingstMap);

private:
    // Timeout time to make the buffer empty when the synchronization does not work
    double BUFFRING_TIMEOUT = 10;

    // Setting information about the online process module
    OnlineProcessingModuleSettings *m_moduleSettings;

    // Flag that indicates the first receiving stream data
    bool m_isFirstStreamData;

    // Time-series buffer for each stream data
    std::map<QString, std::queue<double>> m_timeSeriesDataBuffer;

    // Time buffer for each stream data
    std::map<QString, std::queue<double>> m_timestampDataBuffer;

    // Setting information list for each stream data
    std::map<QString, StreamDataSettings *> &m_streamDataSettingstMap;

    // Time-series data that is synchronized between stream data
    std::map<QString, std::vector<double>> m_synchronizedTimeSeriesData;

    // Time data that is synchronized between stream data
    std::map<QString, std::vector<double>> m_synchronizedTimestampData;

    // Time that is synchronized recently
    double m_lastSynchronizedTime;

    // Enum that indicates the script language
    UbciScriptLanguage m_scriptLanguage;

    // Object that processes by MATLAB
    MatlabInterface *m_matlab;
};

#endif // ONLINEPROCESSINGMODULE_H
