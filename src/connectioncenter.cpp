#include "connectioncenter.h"
#include "transferreceivejob.h"
#include "transfersendjob.h"

#include <QtCore/QThreadPool>

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>


class ConnectionCenter::Private
{
public:
    Private()
        : server(new QTcpServer)
    {}

    ~Private() {
        delete server;
    }


    /** used to handle incoming files */
    QTcpServer *server;

    /** used to keep track of outgoing file transfers */
    // Don't need to keep track. The threadpool deletes the runners that
    // delete the socket

//     QList<QTcpSocket*> connectedPeers;
//     QHash<QString, QTcpSocket*> connectedPeers;

    // key fileName
//     QHash<QString, TransferReceiveJob*>receiveJobs;
    QHash<QString, TransferSendJob*>sendJobs;
};


ConnectionCenter::ConnectionCenter(QObject *parent)
    : QObject(parent)
    , d(new Private)
{
    // setup the server with a casual port. The port number is not a problem as the protocol
    // will send this info to the client that will be connecting.
    if (!d->server->listen()) {
        qDebug() << "[ConnectionCenter::ConnectionCenter] ERROR: can't start server";
    }

    // TODO connect various socket signals
    connect(d->server, &QTcpServer::newConnection, this, &ConnectionCenter::onNewConnection);
}

ConnectionCenter::~ConnectionCenter()
{
    delete d;
}

void ConnectionCenter::onNewConnection()
{
    QTcpSocket *socket = d->server->nextPendingConnection();

    if (!socket) {
        qDebug("ERROR GETTING SOCKET");
        return;
    }

    // TODO security check!! Don't want to allow anyone to connect just for fun
    // someone connected to me. They want to send me a file
//     d->connectedPeers.insert(socket->peerAddress().toString(), socket);

//     QThreadPool::globalInstance()->start(new TransferReceiveJob(socket));
    qDebug("GOT INCOMING CONNECTION");
    TransferReceiveJob *transferRcvJob = new TransferReceiveJob(socket);

//     connect(transferRcvJob, &TransferReceiveJob::finished, [this, transferRcvJob] () {
//         qDebug("TRASNFER OVER. Deleting obj");
//         delete transferRcvJob;
//     });

    connect(transferRcvJob, &TransferReceiveJob::finished, this, &ConnectionCenter::onTransferReceiveJobFinished);
}

void ConnectionCenter::sendFileToClient(const QString &fileName, const QString &ip, int port)
{
    qDebug() << "[ConnectionCenter::sendFileToClient] want to send: " << fileName << " to " << ip << ":" << port;
    TransferSendJob *sendJob = new TransferSendJob(fileName, ip, port);

    d->sendJobs.insert(fileName, sendJob);

    sendJob->startTransfer();
}

quint16 ConnectionCenter::serverPort() const
{
    return d->server->serverPort();
}

void ConnectionCenter::onTransferReceiveJobFinished()
{
    TransferReceiveJob *job = qobject_cast<TransferReceiveJob*>(sender());

    if (!job) {
        qDebug() << "CAN'T CAST TO RCV JOB!";
        return;
    }

    delete job;
}



