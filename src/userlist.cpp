#include "dbhandler.h"
#include "user.h"
#include "userlist.h"

#include <QtCore/QHash>

class UserList::Private
{
public:
    Private()
        : dbHandler(new DbHandler)
    {}

    DbHandler *dbHandler;

    // hash of devices on the LAN. key - uuid
    QHash<QString, User*> users;
};


UserList::UserList(QObject *parent)
    : QObject(parent)
    , d(new Private)
{
}

UserList::~UserList()
{
    qDeleteAll(d->users);
    d->users.clear();

    delete d->dbHandler;
    delete d;
}

void UserList::addUser(const QString &userName, const QString &uuid)
{
    if (!d->users.contains(uuid)) {
        d->users.insert(uuid, new User(userName, uuid));
    }
}

QList<User*> UserList::users() const
{
    return d->users.values();
}
