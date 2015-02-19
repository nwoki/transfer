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
    // load userlist from database
    for (User *user : d->dbHandler->userList()) {
        d->users.insert(user->uuid(), user);
    }
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
        User *user = new User(userName, uuid);

        d->users.insert(uuid, user);
        d->dbHandler->addUser(user);
    }
}

QList<User*> UserList::users() const
{
    return d->users.values();
}
