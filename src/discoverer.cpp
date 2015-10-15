#include "connectioncenter.h"
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
        , connectionCenter(new ConnectionCenter)
    {};

    ~Private() {
        socket->close();
        delete socket;
        delete advertiseTimer;
        delete parser;
        delete connectionCenter;
    }

    UserList *userList;
    QUdpSocket *socket;
    QTimer *advertiseTimer;
    Parser *parser;
    QString uuid;
    ConnectionCenter *connectionCenter;

    /**
     * Holds a list of outgoing file requests towards the clients.
     * The key of the hash is the uuid of the client whilst the value is
     * a list of files awaiting confirmation to be sent.
     */
    QHash<QString, QList<QString>> outgoingFileRequests;
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
    connect(d->parser, &Parser::fileTransferAccepted, this, &Discoverer::onFileTransferAccepted);
    connect(d->parser, &Parser::fileTransferRequest, this, &Discoverer::fileTransferRequestReceived);

    connect(d->socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    connect(d->socket, &QUdpSocket::readyRead, this, &Discoverer::onReadyRead);
}

Discoverer::~Discoverer()
{
    delete d;
}

void Discoverer::acceptFileTransfer(const QString &uuid, const QString &fileName)
{
    if (uuid.isEmpty() || fileName.isEmpty()) {
        return;
    }

    // send a "accept file transfer" request to the client on the LAN.
    // B: "hey, I accept that you send me the file xxx"
    QVariantMap sendFileMap;
    QVariantMap actionMap;

    sendFileMap.insert("sender", Settings::uuid());
    sendFileMap.insert("destination", uuid);
    actionMap.insert("type", "transfer-accept");
    actionMap.insert("fileName", fileName);
    actionMap.insert("port", d->connectionCenter->serverPort());
    sendFileMap.insert("action", actionMap);

    QByteArray advertiseData = QJsonDocument::fromVariant(sendFileMap).toJson(QJsonDocument::Compact);
    d->socket->writeDatagram(advertiseData, QHostAddress::Broadcast, ADVERTISE_PORT);
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

void Discoverer::onFileTransferAccepted(const QString &fromUuid, const QString &fileName, const QString &ip, int port)
{
    // get the file path to send to the client
    QString filePath;

    for (const QString &file : d->outgoingFileRequests.value(fromUuid)) {
        if (QFileInfo(file).fileName() == fileName) {
            filePath = file;

            // update the outgoing list
            QList<QString> taken = d->outgoingFileRequests.take(fromUuid);
            taken.removeOne(file);
            d->outgoingFileRequests.insert(fromUuid, taken);

            break;
        }
    }

    d->connectionCenter->sendFileToClient(filePath, ip, port);
}

void Discoverer::onReadyRead()
{
    while (d->socket->hasPendingDatagrams()) {
        QByteArray datagram;
        QHostAddress senderIp;
        quint16 senderPort;

        datagram.resize(d->socket->pendingDatagramSize());

        d->socket->readDatagram(datagram.data()
                                , datagram.size()
                                , &senderIp
                                , &senderPort);

        // detect host ip(s). We don't want to be parsing our own data
        QStringList hostIps;
        foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
            if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)) {
                hostIps.append(address.toString());
            }
        }

        // TODO remove after parse test
        d->parser->parse(datagram, senderIp.toString());
        // end

        if (!hostIps.contains(senderIp.toString())) {
            d->parser->parse(datagram, senderIp.toString());
        }
    }
}

void Discoverer::sendFileToUser(const QString &uuid)
{
    if (uuid.isEmpty() || d->userList->user(uuid) == nullptr) {
        return;
    }

    // TODO multiple files
    QString file = QFileDialog::getOpenFileName(nullptr, tr("Select file"), QDir::homePath());

    if (file.isEmpty()) {
        return;
    }

    // send a "send file" request to the client on the LAN.
    // A: "hey, I want to send you a file named xxx.
    QVariantMap sendFileMap;
    QVariantMap actionMap;

    sendFileMap.insert("sender", Settings::uuid());
    sendFileMap.insert("destination", uuid);
    actionMap.insert("type", "transfer");
    actionMap.insert("fileName", QFileInfo(file).fileName());
//         actionMap.insert("mimetype", "");       // TODO?? Do I actually need this?
    actionMap.insert("user", Settings::username());
    sendFileMap.insert("action", actionMap);


    QByteArray advertiseData = QJsonDocument::fromVariant(sendFileMap).toJson(QJsonDocument::Compact);
    d->socket->writeDatagram(advertiseData, QHostAddress::Broadcast, ADVERTISE_PORT);

    // and add to the list of outgoing files. This way we know what to send to whom when we receive an "OK, send me
    // the file" confirmation
    QList<QString> files;

    // update files list
    if (!d->outgoingFileRequests.contains(uuid)) {
        files = d->outgoingFileRequests.value(uuid);
        files.append(file);
    }

    // insert files to send to user
    d->outgoingFileRequests.insert(uuid, files);
}
