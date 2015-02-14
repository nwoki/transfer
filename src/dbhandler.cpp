#include "dbhandler.h"
#include "user.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QStandardPaths>

#include <QtSql/QSqlError>


#define DB_SQL_CREATE_QUERY "\
    DROP TABLE IF EXISTS users;\
    -- TODO fix varchar lengths\
    create table users (\
        id int NOT NULL PRIMARY KEY,\
        username varchar (50) NOT NULL,\
        uuid varchar (50) NOT NULL\
-- possible profile image url (to fetch from the internet)\
    );"

class DbHandler::Private
{
public:
    Private()
        : dbLocPath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation))
        , dbFileName("transfer_db.sqlite")
    {}

    QString dbLocPath;
    QString dbFileName;
};


DbHandler::DbHandler()
    : QSqlDatabase("QSQLITE")
    , d(new Private)
{
    bool dbCreateResult = false;

    // check if the database exists
    if (!QFile::exists(d->dbLocPath + QDir::separator() + d->dbFileName)) {
        dbCreateResult = createDatabase();
    }

    // open connection to the db
    if (!dbCreateResult) {
        // TODO show db error message
        qDebug() << "DB ERROR: " << lastError().text();
    }
}

DbHandler::~DbHandler()
{
    close();

    delete d;
}

void DbHandler::addUser(User *user)
{
}

bool DbHandler::createDatabase()
{
    bool success = false;

    // check db dir
    QDir dbDir(d->dbLocPath);
    if (!dbDir.exists()) {
        if (!dbDir.mkpath(d->dbLocPath)) {
            qDebug() << "[DbHandler::createDatabase] ERROR: Can't create database dir @ " << d->dbLocPath;
            return success;
        }
    }

    // create db file
    QFile dbFile(d->dbLocPath + QDir::separator() + d->dbFileName);

    if (dbFile.open(QIODevice::ReadWrite)) {
        dbFile.close();
    } else {
        qDebug() << "[DbHandler::createDatabase] ERROR: Can't create database - " << dbFile.errorString();
        return success;
    }

    setDatabaseName(d->dbLocPath + QDir::separator() + d->dbFileName);

    if (open()) {
        success = true;
        qDebug() << "OPENED DATABAASE";

    } else {
        qDebug() << "DB NOT OPEN. DAFUQ!=";
    }

    qDebug() << "SUCCESS : " << success;
    return success;
}
