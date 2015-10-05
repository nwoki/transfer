#include "dbhandler.h"
#include "user.h"
#include "userlist.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QMetaProperty>

#include <QtWidgets/QFileDialog>


class UserList::Private
{
public:
    Private()
        : dbHandler(new DbHandler)
    {}

    DbHandler *dbHandler;

    // list of user uuid contained in the user list
    QList<QString> userUuids;
    QHash<QString, User*> users;
};


UserList::UserList(QObject *parent)
    : QAbstractListModel(parent)
    , d(new Private)
{
    // load userlist from database
    for (User *user : d->dbHandler->userList()) {
        addUserToModel(user);
    }
}

UserList::~UserList()
{
    qDeleteAll(d->users);
    d->users.clear();
    d->userUuids.clear();

    delete d->dbHandler;
    delete d;
}

void UserList::addUserToModel(User *user)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount() + 1);

    d->userUuids.append(user->uuid());
    d->users.insert(user->uuid(), user);
    d->dbHandler->addUser(user);

    endInsertRows();
}

void UserList::addUser(const QString &userName, const QString &uuid)
{
    if (!d->userUuids.contains(uuid)) {
        User *user = new User(userName, uuid);
        addUserToModel(user);
    } else {
        // treat it as a ping
        d->users.value(uuid)->keepAlive();
    }
}

// void UserList::addUsers(const QList<User*> &users)
// {
//     for (int i = 0; i < users.count(); ++i) {
//         if (!d->users.contains(users.at(i))) {
//             addUser(users.at(i));
//         }
//     }
// }


QVariant UserList::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0) {
        return QVariant();
    } else {
        return d->users.value(d->userUuids.at(index.row()))->data(role);
    }
}

QHash<int, QByteArray> UserList::roleNames() const
{
    /** This method transforms all the object's properties to roles */
    QHash<int, QByteArray> names;

    for (int i = User::staticMetaObject.propertyOffset(); i < User::staticMetaObject.propertyCount(); ++i) {
        names[i] = QByteArray(User::staticMetaObject.property(i).name());
    }

    return names;
}

int UserList::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return d->userUuids.count();
}

QObject* UserList::user(const QString &uuid)
{
    return d->users.value(uuid);
}

void UserList::sendFileToUser(const QString &uuid)
{
    if (uuid.isEmpty() || !d->users.contains(uuid)) {
        return;
    }

    QString file = QFileDialog::getOpenFileName(nullptr, tr("Select file"), QDir::homePath());

    if (file.isEmpty()) {
        return;
    } else {
        Q_EMIT sendFile(uuid, file);
    }
}

// DEPRECATED
void UserList::toggleSelected(const QString &uuid)
{
    qDebug() << "[UserList::toggleSelected] TOGGLING: " << uuid << " from: " << d->users.value(uuid)->isSelected();
    d->users.value(uuid)->toggleSelected();
    qDebug() << "[UserList::toggleSelected] TO: " << d->users.value(uuid)->isSelected();
}


