#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QtCore/QList>
#include <QtCore/QPair>

#include <QtSql/QSqlDatabase>

class User;

/**
 * Handles user storage. Once a user is discovered, the user data is stored
 * on an aux database for loading on application startup.
 */

class DbHandler : public QSqlDatabase
{
public:
    DbHandler();
    ~DbHandler();

    /** adds a user to the database */
    void addUser(User *user);

    /** retrieves the list of saved users on the database
     * first - username
     * second - uuid
     *
     * TODO switch uuid to first place
     */
    QList<QPair<QString, QString>> userList();

private:
    bool createDatabase();

    class Private;
    Private * const d;
};

#endif  // DBHANDLER_H
