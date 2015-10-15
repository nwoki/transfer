#include "transfersendjob.h"

#include <QtCore/QBuffer>
#include <QtCore/QDebug>
#include <QtCore/QFileInfo>
#include <QtCore/QJsonDocument>

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>

#define CHUNK_SIZE 500000


class TransferSendJob::Private
{
public:
    Private()
        : socket(new QTcpSocket)
        , fileNameAck(false)
        , fileTransferAck(false)
    {}

    ~Private()
    {
        if (socket->isOpen()) {
            socket->disconnectFromHost();
        }

        delete socket;
    }


    QString fileName;
    QString peerAddress;
    int peerPort;
    QTcpSocket *socket;

    bool fileNameAck;
    bool fileTransferAck;
};


TransferSendJob::TransferSendJob(const QString &fileName, const QString &peerAddress, int peerPort, QObject *parent)
    : QObject(parent)
    , d(new Private)
{
    d->fileName = fileName;
    d->peerAddress = peerAddress;
    d->peerPort = peerPort;

    connect(d->socket, &QTcpSocket::connected, this, &TransferSendJob::onConnected);
    connect(d->socket, &QTcpSocket::disconnected, this, &TransferSendJob::onDisconnected);
    connect(d->socket, &QTcpSocket::readyRead, this, &TransferSendJob::onReadyRead);
}

TransferSendJob::~TransferSendJob()
{
    delete d;
}

void TransferSendJob::onConnected()
{
    qDebug("CONNECTED");

/**
 *    Don't know if i'm using the SYN byte correctly, but for my protocol, it does its part. The SYN
 *   is used to indicate that the data flow continues.
 *      | STX | FILENAME SIZE + file | ETX |                    -> first PACKET - tells peer file name
 *
 * -> wait for "ok, now send me the file" data (ACK?)
 *
 *      | SOH | data |                                          ->  second PACKET - (and until file end) sends file data
 *      | SYN | data |
 *      | SYN | data | EOT |                                    -> end transmission and file
 */


    // First message tells the peer the name of the file it will be receiving
    QByteArray msg;
    msg += quint8(2);                                   // STX
    msg += QFileInfo(d->fileName).fileName().toUtf8();  // DATA
    msg += quint8(3);                                   // ETX

    d->socket->write(msg);
}

void TransferSendJob::onDisconnected()
{
    qDebug() << "[TransferSendJob] PEER DISCONNECTED";
}

void TransferSendJob::onReadyRead()
{
    qDebug("TransferSendJob::readyRead");

    QByteArray data = d->socket->readAll();
    qDebug() << "GOT: " << data;


    if (quint8(data.at(0)) == 6) {
        qDebug() << "GOT A 6";

        if (!d->fileNameAck) {
            d->fileNameAck = true;
            qDebug() << "SEND - FINISHED FILE NAME TRANSFER";

            // start sending file
            sendFile();
            qDebug() << "SEND - FINISHED";
            d->socket->disconnectFromHost();
        } else {
            // file transfer finished
            d->fileTransferAck = true;
            qDebug() << "SEND - FINISHED FILE TRANSFER";
            Q_EMIT finished(true, QString());
        }
    }
}

void TransferSendJob::sendFile()
{
    qDebug("TransferSendJob::sendFile");
    QFile file(d->fileName);
    qDebug() << "READ FILE OPEN: " << file.open(QIODevice::ReadOnly);

    // TEST shoot all data in at once. Let the QTcpSocket handle how to send it
    d->socket->write(file.readAll());

    // close once finished
    d->socket->disconnectFromHost();
    qDebug() << "DONE SENDING";

//     QByteArray data;
//
//     // setup first byte for sending file
//     int counter = 1;
//
//     data += quint8(1);
//     data += file.read(CHUNK_SIZE);
//
//     qDebug() << "IS SEQUENTIAL? : " << file.isSequential();
//
//     while (file.bytesAvailable() != 0) {
//         qDebug() << "Writing to socket" <<
//         d->socket->write(data);
//
//         // pull new data
//         data.clear();
//         file.seek(CHUNK_SIZE * counter);
//
//         int bytesAvailable = file.bytesAvailable();
//
//         qDebug() << "BYTES AVAILABLE TO SEND - " << bytesAvailable;
//
//         if (bytesAvailable == 0) {
//             break;
//         } else {
//             if (bytesAvailable > CHUNK_SIZE) {
//                 data += file.read(CHUNK_SIZE);
//             } else {
//                 data += file.read(bytesAvailable);
//             }
//
//             counter += 1;
//         }
//     }


    // close the stream
//     d->socket->write(data);
}

void TransferSendJob::startTransfer()
{
    qDebug() << "[TransferSendJob::run] connecting to: " << d->peerAddress << " : " << d->peerPort;

    // connect to the server
    d->socket->connectToHost(QHostAddress(d->peerAddress), d->peerPort);
}
