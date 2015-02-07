#include "user.h"
#include "userlist.h"

#include <QtCore/QHash>

class UserList::Private
{
public:
    Private() {}

    // hash of devices on the LAN. key - uuid
    QHash<QString, User*> users;
};


UserList::UserList()
    : d(new Private)
{

}

UserList::~UserList()
{
    delete d;
}

void UserList::addUser()
{
//     if (!d->users.contains()) {
//         // add;
//
//     }
}

QList<User*> UserList::users() const
{
    return d->users.values();
}
