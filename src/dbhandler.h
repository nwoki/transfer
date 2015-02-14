#ifndef DBHANDLER_H
#define DBHANDLER_H

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

    void addUser(User *user);

private:
    bool createDatabase();

    class Private;
    Private * const d;
};

#endif  // DBHANDLER_H
