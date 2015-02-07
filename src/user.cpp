#include "user.h"

class User::Private
{
public:
    Private() {}

    QString username;
    QString uuid;
};


User::User()
    : d(new Private)
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

QString User::userName() const
{
    return d->username;
}

QString User::uuid() const
{
    return d->uuid;
}
