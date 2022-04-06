#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// CJS-2:
#include "ApplicationSettings.h"
#include "StreamData/StreamDataChartWindow.h"
#include "Utility.h"
#include <QDir>
#include <QFileInfo>

#include <QCloseEvent>
#include <QComboBox>
#include <QListWidget>
#include <QMainWindow>
#include <QSettings>
#include <QStringList>
#include <QTimer>

#include <memory> //for std::unique_ptr

// LSL
#include <lsl_cpp.h>

namespace Ui
{
    class MainWindow;
}

class recording;
class RemoteControlSocket;

class StreamItem
{

public:
    StreamItem(std::string stream_name, std::string stream_type, std::string source_id,
               std::string hostname, bool required)
        : name(stream_name), type(stream_type), id(source_id), host(hostname), checked(required) {}

    QString listName() { return QString::fromStdString(name + " (" + host + ")"); }
    std::string name;
    std::string type;
    std::string id;
    std::string host;
    bool checked;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent, const char *config_file);
    ~MainWindow() noexcept override;

    // CJS-2: Add the log to the log display in the main window
    void WriteLog(const QString &log);

public slots:
    // CJS-2: Deactivate the specified window of the map managed by chart window, by nullptr
    void DisableStreamDataChartWindow(const QString &qWindowName);

    // CJS-2: Stop the stream data recording by pressing the [Stop] button outside the program
    void StopRecording(QString title, QString message);

private slots:
    void statusUpdate(void) const;
    void closeEvent(QCloseEvent *ev) override;
    void blockSelected(const QString &block);
    std::vector<lsl::stream_info> refreshStreams(void);
    void startRecording(void);
    void stopRecording(void);
    void selectAllStreams();
    void selectNoStreams();
    void buildFilename();
    void buildBidsTemplate();
    void printReplacedFilename();
    void enableRcs(bool bEnable);
    void rcsCheckBoxChanged(bool checked);
    void rcsUpdateFilename(QString s);
    void rcsStartRecording();
    void rcsportValueChangedInt(int value);

private:
    QString replaceFilename(QString fullfile) const;
    // function for loading / saving the config file
    QString find_config_file(const char *filename);
    QString counterPlaceholder() const;
    void load_config(QString filename);
    void save_config(QString filename);

    std::unique_ptr<recording> currentRecording;
    std::unique_ptr<RemoteControlSocket> rcs;

    int startTime;
    std::unique_ptr<QTimer> timer;

    QList<StreamItem> knownStreams;
    QSet<QString> missingStreams;
    std::map<std::string, int> syncOptionsByStreamName;

    // QString recFilename;
    QString legacyTemplate;
    std::unique_ptr<Ui::MainWindow> ui; // window pointer

    // @Doug1983 added to suppress pop-ups when remotely starting recording
    // and missing streams or having some unchecked streams
    bool hideWarnings = false;

    // ===== CJS-2 =====

    // Register each setting information of U-BCI based on the setting data read by Lab Recorder's configuration file
    void RegisterUbciSettings(ApplicationSettings *applicationSettings,
                              const QString &settingsFilePath,
                              const std::vector<lsl::stream_info> &requestedAndAvailableStreams);

    // File path of setting
    QString m_settingsFilePath;

    // Chart window of each stream data
    // Manage the name  of stream data
    std::map<std::string, StreamDataChartWindow *> m_streamDataChartWindowMap;
};

#endif // MAINWINDOW_H
