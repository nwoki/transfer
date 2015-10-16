#include "dbhandler.h"
#include "user.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QStandardPaths>

#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>


// TODO check todo's in the db.sql file in the "sql/" folder

#define DB_SQL_CREATE_QUERY "\
    create table users (\
        id INTEGER PRIMARY KEY,\
        username TEXT NOT NULL,\
        uuid TEXT NOT NULL\
    );"

#define DB_FILE_NAME "transfer_db.sqlite"


class DbHandler::Private
{
public:
    Private()
        : dbLocPath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation))
        , dbFileName(DB_FILE_NAME)
        , dbStatus(false)
    {
    }

    QString dbLocPath;
    QString dbFileName;
    bool dbStatus;
};


DbHandler::DbHandler()
    : QSqlDatabase("QSQLITE")
    , d(new Private)
{
    // check if the database exists
    if (!QFile::exists(d->dbLocPath + QDir::separator() + d->dbFileName)) {
        d->dbStatus = createDatabase();
    } else {
        setDatabaseName(d->dbLocPath + QDir::separator() + d->dbFileName);

        d->dbStatus = open();
        qDebug() << "[DbHandler::DbHandler] opening database @ " << databaseName() << " : " << d->dbStatus;

        if (!d->dbStatus) {
            qDebug() << "[DbHandler::DbHandler] can't open db: " << lastError().text();
        }
    }

    // open connection to the db
    if (!d->dbStatus) {
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
    qDebug("[DbHandler::addUser]");

    if (!d->dbStatus) {
        return;
    }

    // check if user exists on the database
    QSqlQuery existQuery = exec(QString("select id from users where uuid=\"%1\";").arg(user->uuid()));

    if (existQuery.lastError().type() != QSqlError::NoError) {
        qDebug() << "[DbHandler::createDatabase] ERROR: " << existQuery.lastError().text();
        return;
    }

    QString userId;

    // check the result of the query.
    if (!existQuery.next()) {
        qDebug() << "[DbHandler::addUser] no record of user with uuid = " << user->uuid();

        QSqlQuery addUserQuery = exec(QString("insert into users values (NULL, \"%1\", \"%2\")")
                                .arg(user->userName())
                                .arg(user->uuid()));

        if (addUserQuery.lastError().type() != QSqlError::NoError) {
            qDebug() << "[DbHandler::addUser] ERROR: " << addUserQuery.lastError().text();
        }
    }
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

        // now create the db
        QSqlQuery createQuery = exec(DB_SQL_CREATE_QUERY);

        if (createQuery.lastError().type() != QSqlError::NoError) {
            qDebug() << "[DbHandler::createDatabase] ERROR: " << createQuery.lastError().text();
            success = false;
        }
    } else {
        qDebug() << "[DbHandler::createDatabase] ERROR: can't open database - " << lastError().text();
        success = false;
    }

    return success;
}

QList<QPair<QString, QString>> DbHandler::userList()
{
    QList<QPair<QString, QString>> userList;
    QSqlQuery extractionQuery = exec(QString("select uuid, username from users"));

    if (extractionQuery.lastError().type() == QSqlError::NoError) {

        while (extractionQuery.next()) {
            userList.append(QPair<QString, QString>(extractionQuery.value(0).toString()
                                                    , extractionQuery.value(1).toString()));
        }

    } else {
        qDebug()<< "[DbHandler::userList] ERROR: " << extractionQuery.lastError().text();
    }

    return userList;
}
