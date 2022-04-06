#ifndef HTTPOUTPUTMODULE_H
#define HTTPOUTPUTMODULE_H

#include "mainwindow.h"

#include <QNetworkAccessManager>
#include <QObject>
#include <QtNetwork>
#include <QUrl>

// Output the data by HTTP protocol
class HttpOutputModule : public QObject
{
    Q_OBJECT

public:
    HttpOutputModule(const QUrl &serverUrl,
                     const QString &getParameterKey,
                     MainWindow *mainWindow);

    ~HttpOutputModule();

public slots:
    // Add the first component of result data to the GET parameter in URL and output
    void OutputData(const QString &onlineProcessingModuleName,
                    const std::shared_ptr<std::vector<double>> resultsData);

    //　Process the reponse from the server
    void ProcessReply(QNetworkReply *reply);

signals:
    // Request to stop the recording of the streaming data to the main window when the connection error occurr
    void RequestRecordingStop(QString title, QString message);

private:
    // Send the GET request data
    void SendGetRequest(const QUrl &url);

    // Object that does the HTTP connection
    QNetworkAccessManager *m_networkAccessManager;

    // URL of the server
    QUrl m_serverUrl;

    // Key parameter of GET
    QString m_getParameterKey;

    // Flag that indicates whether there is an connection error
    bool m_isInCommunicationError;
};

#endif // HTTPOUTPUTMODULE_H
