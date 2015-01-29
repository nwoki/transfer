#include "discoverer.h"

#include <QtCore/QTimer>

#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QUdpSocket>


#define ADVERTISE_PORT 5555

class Discoverer::Private
{
public:
    Private()
        : socket(new QUdpSocket)
        , advertiseTimer(new QTimer)
        {};

    QUdpSocket *socket;
    QTimer *advertiseTimer;
};


Discoverer::Discoverer(QObject *parent)
    : QObject(parent)
    , d(new Private)
{
    connect(d->advertiseTimer, &QTimer::timeout, this, &Discoverer::advertise);

    d->socket->bind(QHostAddress::AnyIPv4, ADVERTISE_PORT, QAbstractSocket::ShareAddress);
    d->advertiseTimer->setInterval(2500);
    d->advertiseTimer->start();


    connect(d->socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));

    connect(d->socket, &QUdpSocket::readyRead, [this] () {
        while (d->socket->hasPendingDatagrams()) {
            QByteArray datagram;
            QHostAddress sender;
            quint16 senderPort;

            datagram.resize(d->socket->pendingDatagramSize());

            d->socket->readDatagram(datagram.data()
                                    , datagram.size()
                                    , &sender
                                    , &senderPort);

            // detect host ip(s). We don't want to be parsing our own data
            QStringList hostIps;
            foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
                if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)) {
                    hostIps.append(address.toString());
                }
            }

            if (!hostIps.contains(sender.toString())) {
                qDebug() << "DATAGRAM RECEIVED: " << datagram;
            }
        }
    });
}

Discoverer::~Discoverer()
{
    delete d->socket;
    delete d->advertiseTimer;
    delete d;
}

void Discoverer::advertise()
{
    // TODO define discovery protocol
    d->socket->writeDatagram("BUBBUBUBA", QHostAddress::Broadcast, ADVERTISE_PORT);
}

void Discoverer::onError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "ERROR: " << socketError;
    qDebug() << d->socket->errorString();
}
