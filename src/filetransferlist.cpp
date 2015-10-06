#include "filetransfer.h"
#include "filetransferlist.h"

#include <QtCore/QDebug>
#include <QtCore/QMetaProperty>


class FileTransferList::Private
{
public:
    Private()
//     : dbHandler(new DbHandler)
    {}

//     DbHandler *dbHandler;

    // list of user uuid contained in the user list
    QList<FileTransfer*> fileTransfers;
};


FileTransferList::FileTransferList(QObject *parent)
    : QAbstractListModel(parent)
    , d(new Private)
{
    // TODO load pending trasfers from database
//     for (User *user : d->dbHandler->userList()) {
//         addUserToModel(user);
//     }
}

FileTransferList::~FileTransferList()
{
    qDeleteAll(d->fileTransfers);
    d->fileTransfers.clear();

//     delete d->dbHandler;
    delete d;
}

void FileTransferList::addFileTransferToModel(FileTransfer *fileTransfer)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount() + 1);
    d->fileTransfers.append(fileTransfer);
    endInsertRows();
}

void FileTransferList::addFileTransfer(const QString &userName, const QString &fileName, const QString &userUuid)
{
    addFileTransferToModel(new FileTransfer(userName, fileName, userUuid));
}

QVariant FileTransferList::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0) {
        return QVariant();
    } else {
        return d->fileTransfers.at(index.row())->data(role);
    }
}

QHash<int, QByteArray> FileTransferList::roleNames() const
{
    /** This method transforms all the object's properties to roles */
    QHash<int, QByteArray> names;

    for (int i = FileTransfer::staticMetaObject.propertyOffset(); i < FileTransfer::staticMetaObject.propertyCount(); ++i) {
        names[i] = QByteArray(FileTransfer::staticMetaObject.property(i).name());
    }

    return names;
}

int FileTransferList::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return d->fileTransfers.count();
}

// QObject* FileTransferList::user(const QString &uuid)
// {
//     return d->users.value(uuid, nullptr);
// }


