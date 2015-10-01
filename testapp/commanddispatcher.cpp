// {
// sender: uuid
// action: {
//          type: advertise
//          user: <username>
// }
//
// action: {
//          type: transfer
//          fileName: <fileName>
//          mimetype: <type>
//          user: <username>
// }
//
// destination: uuid/<empty>
// }
//
#include "commanddispatcher.h"

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QVariantMap>

#include <QtNetwork/QUdpSocket>


class CommandDispatcher::Private
{
public:
    Private()
        : port(0)
        , udpSocket(new QUdpSocket)
    {}

    int port;
    QUdpSocket *udpSocket;
};


CommandDispatcher::CommandDispatcher(int port)
    : d(new Private)
{
    d->port = port;
}

CommandDispatcher::~CommandDispatcher()
{
    delete d->udpSocket;
    delete d;
}

void CommandDispatcher::advertise()
{
    qDebug() << "DISPATCHIng";

    // send advertisement
    QVariantMap advertiseMap;
    QVariantMap actionMap;

    advertiseMap.insert("sender", "35a1bbc3-af74-499b-a337-be3248453894");
    advertiseMap.insert("destination", "");

    actionMap.insert("type", "advertise");
    actionMap.insert("user", "test-app");
    advertiseMap.insert("action", actionMap);

    QByteArray advertiseData = QJsonDocument::fromVariant(advertiseMap).toJson(QJsonDocument::Compact);

    d->udpSocket->writeDatagram(advertiseData, QHostAddress::Broadcast, d->port);
}

