#include "user.h"

#include <QtCore/QMetaProperty>


class User::Private
{
public:
    Private() {}

    QString username;
    QString uuid;
};


User::User(QObject *parent)
    : QObject(parent)
    , d(new Private)
{
}

User::User(const QString &userName, const QString &uuid)
    : d(new Private)
{
    d->username = userName;
    d->uuid = uuid;
}

User::~User()
{
    delete d;
}

QVariant User::data(int role) const
{
    return metaObject()->property(role).read(this);
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

