#ifndef USERLIST_H
#define USERLIST_H

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QString>

class User;

/**
 * Class used to keep track of users on the LAN and to provide a
 * model of these users when needed
 */

class UserList : public QObject
{
    Q_OBJECT

public:
    UserList(QObject *parent = 0);
    ~UserList();

    QList<User*> users() const;

public Q_SLOTS:
    /** adds a user to the list */
    void addUser(const QString &userName, const QString &uuid);

private:
    class Private;
    Private * const d;
};


#endif  // USERLIST_H
