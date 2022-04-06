#include "OutputModuleSettings.h"

#include <QDebug>

// Hold the setting information related to the online processing module
OutputModuleSettings::OutputModuleSettings(const QSettings &settings) : m_udpSenderPortNum(0),
                                                                        m_httpGetParameterKey("U-BCI")
{
    // Set the IP address of the UDP-receiving PC
    if (settings.contains("UdpOutputModule/ReceiverIPAddress"))
    {
        QString ipAddress = settings.value("UdpOutputModule/ReceiverIPAddress").toString();
        if (ipAddress == "localhost")
            m_udpReceiverIpAddress = QHostAddress::LocalHost;
        else
            m_udpReceiverIpAddress = QHostAddress(ipAddress);
    }

    // Set the port number of the UDP-receiving PC
    if (settings.contains("UdpOutputModule/ReceiverPortNum"))
        m_udpReceiverPortNum = settings.value("UdpOutputModule/ReceiverPortNum").toUInt();

    // Set the IP address of the UDP-sending PC
    if (settings.contains("UdpOutputModule/SenderIPAddress"))
    {
        QString ipAddress = settings.value("UdpOutputModule/SenderIPAddress").toString();
        if (ipAddress == "localhost")
            m_udpSenderIpAddress = QHostAddress::LocalHost;
        else
            m_udpSenderIpAddress = QHostAddress(ipAddress);
    }

    // Set the port number of the UDP-sending PC
    if (settings.contains("UdpOutputModule/SenderPortNum"))
        m_udpSenderPortNum = settings.value("UdpOutputModule/SenderPortNum").toUInt();

    // Set the URL of HTTP protocol server
    if (settings.contains("HttpOutputModule/Url"))
    {
        QString url = settings.value("HttpOutputModule/Url").toString();
        m_httpServerUrl = QUrl(url);
    }

    // Set the parameter key  of HTTP GET request
    if (settings.contains("HttpOutputModule/Key"))
        m_httpGetParameterKey = settings.value("HttpOutputModule/Key").toString();
}

// Show all the settings for debug to the Qt console
void OutputModuleSettings::ShowSettings()
{
    qDebug() << "\n[Output module settings]";
    qDebug() << "UDP receiver IP address:" << m_udpReceiverIpAddress;
    qDebug() << "UDP receiver port#:" << m_udpReceiverPortNum;
    qDebug() << "UDP sender IP address:" << m_udpSenderIpAddress;
    qDebug() << "UDP sender port#:" << m_udpSenderPortNum;
    qDebug() << "HTTP server URL:" << m_httpServerUrl;
    qDebug() << "HTTP GET parameter key:" << m_httpGetParameterKey;
}
