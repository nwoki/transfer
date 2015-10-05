#include "connectioncenter.h"

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
    QList<QTcpSocket> ongoingTransfers;
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
}

ConnectionCenter::~ConnectionCenter()
{
    delete d;
}

