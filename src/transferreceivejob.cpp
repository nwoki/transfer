#include "settings.h"
#include "transferreceivejob.h"

#include <QtCore/QDir>
#include <QtCore/QFile>

#include <QtNetwork/QTcpSocket>


class TransferReceiveJob::Private
{
public:
    Private()
        : socket(nullptr)
        , file(nullptr)
    {}

    ~Private()
    {
        if (socket->isOpen()) {
            qDebug("RECEIVE_JOB - SOCKET OPEN, DISCONNECTING");
            socket->disconnectFromHost();
        } else {
            qDebug("RCV - SOCKET ISN't OPEN");
        }

        // TODO check this out
//         delete socket;
    }

    QString incomingFileName;
    QTcpSocket *socket;
    QFile *file;
};


TransferReceiveJob::TransferReceiveJob(QTcpSocket *peerConnection, QObject *parent)
    : QObject(parent)
    , d(new Private)
{
    d->socket = peerConnection;

    connect(d->socket, &QTcpSocket::readyRead, this, &TransferReceiveJob::onReadyRead);
//     connect(d->socket, &QTcpSocket::disconnected, this, &TransferReceiveJob::finished);
    connect(d->socket, &QTcpSocket::disconnected, [this] () {
        qDebug() << "FINISHED RECEIVING FILE. WRAP THIS SHIT UP";
//         d->file->flush();
        d->file->close();

        Q_EMIT finished();
    });
}

TransferReceiveJob::~TransferReceiveJob()
{
    qDebug("[TransferReceiveJob::~TransferReceiveJob]");
    delete d;
}

#include <QtCore/QEventLoop>
void TransferReceiveJob::onReadyRead()
{
    QByteArray data = d->socket->readAll();
//     qDebug() << "INCOMING: " << data;

//     | START-BYTE | file | ETX |                              -> first PACKET
//     | SYN | data |                                           ->  until file end
//     | SYN | data | EOT |                                     -> end transmission and file

    // check what type of packet we're dealing with
    if (data.startsWith(quint8(2)) && data.endsWith(quint8(3))) {
        // got file name of the data to be transmitted

        d->incomingFileName = data.mid(1, (data.size() - 2));
        qDebug() << "FILE TO RCV: " << d->incomingFileName;

        // file data start. Initiate saving data to file
        d->file = new QFile(Settings::downloadDir() + QDir::separator() + d->incomingFileName);

        if (!d->file->open(QIODevice::WriteOnly)) {
            qDebug() << "CAN'T OPEN FILE: " << d->file->fileName();

            // TODO return NACK -> so we know there was an error
            return;
        }
        // return an ACK so that the peer can start sending the file we accepted
        sendAck();
    } else {
        qDebug() << "GOT DATA. JUST APPEND";
        // TODO minimum check. Just check if the ack has been sent.
        // TODO initial handshake-auth process. So we know the client connected is ok
        saveDataToFile(data);
    }
}

void TransferReceiveJob::saveDataToFile(const QByteArray &data)
{
    // just an ignorant write to file

    // check the stream is open
    // TODO handle
    if (!d->file->isOpen()) {
        qDebug() << "RE-OPENING FILE: " << d->file->open(QIODevice::WriteOnly);
    }

    // write
    d->file->write(data);
}

void TransferReceiveJob::sendAck()
{
    QByteArray msg;
    msg += quint8(6);   // ACK

    d->socket->write(msg);
}

