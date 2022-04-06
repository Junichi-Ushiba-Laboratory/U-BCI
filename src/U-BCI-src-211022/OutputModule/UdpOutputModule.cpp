#include "UdpOutputModule.h"

#include <QDebug>

UdpOutputModule::UdpOutputModule(OutputModuleSettings *outputModuleSettings) : m_receiverIpAddress(outputModuleSettings->GetUdpReceiverIpAddress()),
                                                                               m_receiverPortNum(outputModuleSettings->GetUdpReceiverPortNum())
{
    if (!(outputModuleSettings->GetUdpSenderIpAddress().isNull() &&
          outputModuleSettings->GetUdpSenderPortNum() == 0))
        m_udpSocket.bind(outputModuleSettings->GetUdpSenderIpAddress(),
                         outputModuleSettings->GetUdpSenderPortNum());

    qInfo() << "\"UDP output module\""
            << ": Launched.";
}

UdpOutputModule::~UdpOutputModule()
{
    qInfo() << "\"UDP output module\""
            << ": Closed.";
}

// Output the data
void UdpOutputModule::OutputData(
    const QString &onlineProcessingModuleName,
    const std::shared_ptr<std::vector<double>> resultsData)
{
    QByteArray datagram;
    QDataStream dataStream(&datagram, QIODevice::WriteOnly);
    dataStream.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    // Convert the double array to binary data
    // 4 byte data that indicates the data size will be added to the head by QDataStream
    dataStream << QByteArray::fromRawData(
        reinterpret_cast<const char *>(resultsData->data()),
        resultsData->size() * sizeof(double));

    // Send binary data to the specified port of localhost
    m_udpSocket.writeDatagram(datagram, m_receiverIpAddress, m_receiverPortNum);
}
