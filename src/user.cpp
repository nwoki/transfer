#include "user.h"

#include <QtCore/QDebug>
#include <QtCore/QMetaProperty>
#include <QtCore/QTimer>


class User::Private
{
public:
    Private()
        : selected(false)
        , online(false)
        , onlineTimer(new QTimer)
    {
        onlineTimer->setInterval(10000);
    }

    bool selected;
    bool online;
    QString username;
    QString uuid;

    QTimer *onlineTimer;
};


User::User(QObject *parent)
    : QObject(parent)
    , d(new Private)
{
    d->onlineTimer->start();
    connect(d->onlineTimer, &QTimer::timeout, this, &User::onlineTimerTimeout);
}

User::User(const QString &userName, const QString &uuid)
    : d(new Private)
{
    d->username = userName;
    d->uuid = uuid;
    d->onlineTimer->start();

    connect(d->onlineTimer, &QTimer::timeout, this, &User::onlineTimerTimeout);
}

User::~User()
{
    delete d->onlineTimer;
    delete d;
}

QVariant User::data(int role) const
{
    return metaObject()->property(role).read(this);
}

bool User::isSelected() const
{
    return d->selected;
}

void User::keepAlive()
{
    qDebug() << "[User::keepAlive] for: " << d->username;

    // restart the timer
    d->onlineTimer->stop();

    if (!d->online) {
        d->online = true;
        Q_EMIT onlineStatusChanged();
    }

    d->onlineTimer->start();
}

bool User::online() const
{
    return d->online;
}

void User::onlineTimerTimeout()
{
    d->online = false;
    Q_EMIT onlineStatusChanged();
}

void User::toggleSelected()
{
    if (d->selected) {
        d->selected = false;
    } else {
        d->selected = true;
    }

    Q_EMIT userDataChanged();
}

QString User::userName() const
{
    return d->username;
}

QString User::uuid() const
{
    return d->uuid;
}

bool User::operator==(const User &user)
{
    bool match = false;

    if (this->userName() == user.userName()
        && this->uuid() == user.uuid()) {
        match = true;
    }

    return match;
}

