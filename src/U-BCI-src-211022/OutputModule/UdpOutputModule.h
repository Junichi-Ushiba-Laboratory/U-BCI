#ifndef UDPOUTPUTMODULE_H
#define UDPOUTPUTMODULE_H

#include "OutputModuleSettings.h"

#include <QDataStream>
#include <QObject>
#include <QtNetwork/QUdpSocket>

// Output the data by UDP
class UdpOutputModule : public QObject
{
    Q_OBJECT

public:
    UdpOutputModule(OutputModuleSettings *outputModuleSettings);

    ~UdpOutputModule();

public slots:
    // Output the data
    void OutputData(const QString &onlineProcessingModuleName,
                    const std::shared_ptr<std::vector<double>> resultsData);

private:
    // IP address of the UDP-receiving PC
    QUdpSocket m_udpSocket;

    // IP address of the host
    const QHostAddress m_receiverIpAddress;

    // Port number of the UDP-receiving PC
    const unsigned int m_receiverPortNum;
};

#endif // UDPOUTPUTMODULE_H
