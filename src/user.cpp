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
