#include "udpbroadcast.h"

UDPBroadcast::UDPBroadcast(QObject *parent) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);

    localHostName = QHostInfo::localHostName();
    setBroadcastAddresses();

    udpSocket->bind(QHostAddress::Any, 37282);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingMessages()));
}

UDPBroadcast::~UDPBroadcast()
{
    delete udpSocket;
}

void UDPBroadcast::broadcastMessage(QString message)
{
    message.prepend(localHostName + "@" + QTime::currentTime().toString() + ": ");
    foreach (const QHostAddress &broadcastAddress, broadcastAddresses)
        udpSocket->writeDatagram(message.toUtf8(), broadcastAddress, 37282);
}

void UDPBroadcast::readPendingMessages()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray message;
        message.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(message.data(), message.size());
        emit notifyNewMessage(QVariant(message));
    }
}

void UDPBroadcast::setBroadcastAddresses()
{
    foreach (const QNetworkInterface &interface, QNetworkInterface::allInterfaces()) {
        foreach (const QNetworkAddressEntry &address, interface.addressEntries()) {
            QHostAddress broadcastAddress = address.broadcast();
            if (!address.broadcast().isNull() && !broadcastAddresses.contains(broadcastAddress))
                broadcastAddresses.append(broadcastAddress);
        }
    }
}
