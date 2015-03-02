#ifndef USERLIST_H
#define USERLIST_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QString>


class User;

/**
 * Class used to keep track of users on the LAN and to provide a
 * model of these users when needed
 */

class UserList : public QAbstractListModel
{
    Q_OBJECT

public:
    UserList(QObject *parent = 0);
    ~UserList();

    QHash<int, QByteArray> roleNames() const;

public Q_SLOTS:
    /** adds a user to the list */
    void addUser(const QString &userName, const QString &uuid);
//     void addUsers(const QList<User*> &users);

private:
    void addUserToModel(User *user);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &index = QModelIndex()) const;

    class Private;
    Private * const d;
};


#endif  // USERLIST_H
