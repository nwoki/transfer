#include "parser.h"
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

void Parser::parse(const QByteArray &data)
{
    QJsonParseError jsonError;
    QJsonObject rootObj = QJsonDocument::fromJson(data, &jsonError).object();

    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "[Parser::parse] ERROR: " << jsonError.errorString();
        return;
    }

    QJsonObject actionObj = rootObj.value("action").toObject();

    if (actionObj.value("type").toString() == "advertise") {
        qDebug() << "user discovered: " << actionObj.value("user").toString() << rootObj.value("uuid").toString();
        Q_EMIT userDiscovered(actionObj.value("user").toString(), rootObj.value("uuid").toString());
    }

    // TODO the other actions
}
