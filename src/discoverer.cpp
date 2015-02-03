#include "device.h"
#include "discoverer.h"
#include "settings.h"

#include <QtCore/QJsonDocument>
#include <QtCore/QSettings>
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
        , uuid(Settings::uuid())
    {};

    QUdpSocket *socket;
    QTimer *advertiseTimer;
    QString uuid;

    // hash of devices on the LAN. key - uuid
    QHash<QString, Device*> devices;
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
                // TODO parser
            }
        }
    });
}

Discoverer::~Discoverer()
{
    delete d->socket;
    delete d->advertiseTimer;

    qDeleteAll(d->devices);
    d->devices.clear();

    delete d;
}

void Discoverer::advertise()
{
    // TODO define discovery protocol
    /*
     * {
     * sender: uuid
     * action: {
     *          type: advertise
     *          user: <username>
     * }
     *
     * action: {
     *          type: transfer
     *          fileName: <fileName>
     *          mimetype: <type>
     *          user: <username>
     * }
     *
     * destination: uuid/<empty>
     * }
     */
    QVariantMap advertiseMap;
    QVariantMap actionMap;

    advertiseMap.insert("sender", Settings::uuid());
    advertiseMap.insert("destination", "");

    actionMap.insert("type", "advertise");
    actionMap.insert("user", Settings::username());
    advertiseMap.insert("action", actionMap);

    QByteArray advertiseData = QJsonDocument::fromVariant(advertiseMap).toJson(QJsonDocument::Compact);

    d->socket->writeDatagram(advertiseData, QHostAddress::Broadcast, ADVERTISE_PORT);
}

void Discoverer::onError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "ERROR: " << socketError;
    qDebug() << d->socket->errorString();
}
