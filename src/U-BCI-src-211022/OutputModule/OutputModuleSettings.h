#ifndef OUTPUTMODULESETTINGS_H
#define OUTPUTMODULESETTINGS_H

#include "ApplicationSettings.h"

#include <QHostAddress>
#include <QSettings>
#include <QUrl>

// Hold the setting information related to the data output module
class OutputModuleSettings
{
public:
    // Give the setting data read by the Lab Recorder's configuration file and generate the object
    OutputModuleSettings(const QSettings &settings);

    // Get the IP address of the UDP-receiving PC
    const QHostAddress &GetUdpReceiverIpAddress() { return m_udpReceiverIpAddress; }

    // Get the port number of the UDP-receiving PC
    const unsigned int GetUdpReceiverPortNum() { return m_udpReceiverPortNum; }

    // Get the IP address of the UDP-sending PC
    const QHostAddress &GetUdpSenderIpAddress() { return m_udpSenderIpAddress; }

    // Get the port number of the UDP-sending PC
    const unsigned int GetUdpSenderPortNum() { return m_udpSenderPortNum; }

    // Get the URL of the HTTP protocol server
    const QUrl &GetHttpServerUrl() { return m_httpServerUrl; }

    // Get the parameter key of the HTTP GET request
    const QString &GetHttpGetParameterKey() { return m_httpGetParameterKey; }

    // Show all the settings for debug to the Qt console
    void ShowSettings();

private:
    // IP address of the UDP-receiving PC
    QHostAddress m_udpReceiverIpAddress;

    // Port number of the UDP-receiving PC
    unsigned int m_udpReceiverPortNum;

    // IP address of the UDP-sending PC
    QHostAddress m_udpSenderIpAddress;

    // Port number of the UDP-sending PC
    unsigned int m_udpSenderPortNum;

    // URL of the HTTP protocol server
    QUrl m_httpServerUrl;

    // Key parameter of HTTP GET request
    QString m_httpGetParameterKey;
};

#endif // OUTPUTMODULESETTINGS_H
