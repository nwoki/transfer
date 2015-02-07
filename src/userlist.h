#ifndef USERLIST_H
#define USERLIST_H

#include <QtCore/QList>

class User;

/**
 * Class used to keep track of users on the LAN and to provide a
 * model of these users when needed
 */

class UserList
{
public:
    UserList();
    ~UserList();

    /** adds a user to the list */
    void addUser();

    QList<User*> users() const;

private:
    class Private;
    Private * const d;
};


#endif  // USERLIST_H
