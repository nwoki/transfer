#include "parser.h"
#include "settings.h"
#include "user.h"

#include <QtCore/QDebug>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonParseError>
#include <QtCore/QJsonObject>

class Parser::Private
{
public:
    Private() {}
};


Parser::Parser(QObject *parent)
    : QObject(parent)
    , d(new Private)
{
}

Parser::~Parser()
{
    delete d;
}

void Parser::parse(const QByteArray &data, const QString &senderIp)
{
    QJsonParseError jsonError;
    QJsonObject rootObj = QJsonDocument::fromJson(data, &jsonError).object();

    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "[Parser::parse] ERROR: " << jsonError.errorString();
        return;
    }

    QJsonObject actionObj = rootObj.value("action").toObject();
    QString actionType = actionObj.value("type").toString();

    QString destination = rootObj.value("destination").toString();

    // check that I'm the desired recipient
    if (destination != Settings::uuid() && !destination.isEmpty()) {
        qDebug() << "NOT for me!";
        return;
    }

    if (actionType == "advertise") {
        qDebug() << "user discovered: " << actionObj.value("user").toString() << rootObj.value("sender").toString();
        Q_EMIT userDiscovered(actionObj.value("user").toString(), rootObj.value("sender").toString());
    } else if (actionType == "transfer") {
        qDebug() << "USER: " << actionObj.value("user").toString() << " wants to send you: " << actionObj.value("fileName").toString();
        Q_EMIT fileTransferRequest(actionObj.value("user").toString()
                                , actionObj.value("fileName").toString()
                                , rootObj.value("destination").toString());
    } else if (actionType == "transfer-accept") {
        qDebug() << "TRANSFER ACCEPT - START SENDING FILE TO CLIENT";
        Q_EMIT fileTransferAccepted(rootObj.value("sender").toString()
                                , actionObj.value("fileName").toString()
                                , senderIp
                                , actionObj.value("port").toInt());
    }

    // TODO the other actions
}
