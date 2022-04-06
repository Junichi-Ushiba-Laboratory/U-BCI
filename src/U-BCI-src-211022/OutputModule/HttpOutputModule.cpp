#include "HttpOutputModule.h"

HttpOutputModule::HttpOutputModule(const QUrl &serverUrl,
                                   const QString &getParameterKey,
                                   MainWindow *mainWindow) : m_serverUrl(serverUrl),
                                                             m_getParameterKey(getParameterKey),
                                                             m_isInCommunicationError(false)
{
    // Generate the object that does HTTP connection
    m_networkAccessManager = new QNetworkAccessManager(this);

    // Call the function that process the response from the server
    connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(ProcessReply(QNetworkReply *)));

    // Set Signal / Slot that stops the program when connection error occurr
    connect(this, &HttpOutputModule::RequestRecordingStop,
            mainWindow, &MainWindow::StopRecording);

    qInfo() << "\"HTTP output module\""
            << ": Launched.";
}

HttpOutputModule::~HttpOutputModule()
{
    delete m_networkAccessManager;

    qInfo() << "\"HTTP output module\""
            << ": Closed.";
}

// Add the first component of result data to the GET parameter in URL and output
void HttpOutputModule::OutputData(
    const QString &onlineProcessingModuleName,
    const std::shared_ptr<std::vector<double>> resultsData)
{
    // Add the first component of result data to the GET parameter in URL
    QUrlQuery query;
    query.addQueryItem(m_getParameterKey, QString::number(resultsData->at(0)));
    m_serverUrl.setQuery(query);

    // Send the GET request data
    SendGetRequest(m_serverUrl);
}

// Send the GET request data
void HttpOutputModule::SendGetRequest(const QUrl &url)
{
    m_networkAccessManager->get(QNetworkRequest(url));
}

//　Process the reponse from the server
void HttpOutputModule::ProcessReply(QNetworkReply *reply)
{
    if (m_isInCommunicationError)
        return;

    QString message;
    if (reply->error() == QNetworkReply::NoError)
    {
        message = reply->readAll();
        qInfo() << message;
        reply->deleteLater();
        reply = nullptr;
    }
    else
    {
        m_isInCommunicationError = true;
        message += "HTTP communication error occurred.\n\n";
        message += reply->errorString();
        reply->deleteLater();
        reply = nullptr;

        // Stop the program
        emit RequestRecordingStop("HTTP Communication Error", message);
    }
}
