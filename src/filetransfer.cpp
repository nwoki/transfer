#include "filetransfer.h"

#include <QtCore/QMetaProperty>


class FileTransfer::Private
{
public:
    Private() {}

    QString fileName;
    QString userName;
    QString userUuid;
};


FileTransfer::FileTransfer(QObject *parent)
    : QObject(parent)
    , d(new Private)
{
}

FileTransfer::FileTransfer(const QString &userName, const QString &fileName, const QString &userUuid, QObject *parent)
    : QObject(parent)
    , d(new Private)
{
    d->userName = userName;
    d->fileName = fileName;
    d->userUuid = userUuid;
}

FileTransfer::~FileTransfer()
{
    delete d;
}

QVariant FileTransfer::data(int role) const
{
    return metaObject()->property(role).read(this);
}

QString FileTransfer::fileName() const
{
    return d->fileName;
}

QString FileTransfer::userName() const
{
    return d->userName;
}

QString FileTransfer::userUuid() const
{
    return d->userUuid;
}

bool FileTransfer::operator==(const FileTransfer &fileTransfer)
{
    bool match = false;

    if (this->userName() == fileTransfer.userName()
        && this->userUuid() == fileTransfer.userUuid()
        && this->fileName() == fileTransfer.fileName()) {
        match = true;
    }

    return match;
}

