#include "discoverer.h"
#include "parser.h"
#include "settings.h"
#include "userlist.h"

#include <QtCore/QDir>
#include <QtCore/QJsonDocument>
#include <QtCore/QSettings>
#include <QtCore/QTimer>

#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QUdpSocket>

#include <QtWidgets/QFileDialog>


#define ADVERTISE_PORT 5555

class Discoverer::Private
{
public:
    Private(UserList *userlist)
        : userList(userlist)
        , socket(new QUdpSocket)
        , advertiseTimer(new QTimer)
        , parser(new Parser)
        , uuid(Settings::uuid())
    {};

    UserList *userList;
    QUdpSocket *socket;
    QTimer *advertiseTimer;
    Parser *parser;
    QString uuid;
};


Discoverer::Discoverer(UserList *userlist, QObject *parent)
    : QObject(parent)
    , d(new Private(userlist))
{
    connect(d->advertiseTimer, &QTimer::timeout, this, &Discoverer::advertise);

    d->socket->bind(QHostAddress::AnyIPv4, ADVERTISE_PORT, QAbstractSocket::ShareAddress);
    d->advertiseTimer->setInterval(2500);
    d->advertiseTimer->start();

    connect(d->parser, &Parser::userDiscovered, d->userList, &UserList::addUser);
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

            // TODO remove after parse test
            d->parser->parse(datagram);
            // end

            if (!hostIps.contains(sender.toString())) {
                d->parser->parse(datagram);
            }
        }
    });
}

Discoverer::~Discoverer()
{
    delete d->socket;
    delete d->advertiseTimer;
    delete d->parser;
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

void Discoverer::sendFileToUser(const QString &uuid)
{
    if (uuid.isEmpty() || d->userList->user(uuid) == nullptr) {
        return;
    }

    QString file = QFileDialog::getOpenFileName(nullptr, tr("Select file"), QDir::homePath());

    if (file.isEmpty()) {
        return;
    } else {
        Q_EMIT sendFile(uuid, file);
    }
}
