#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include <QtCore/QString>
#include <QtCore/QVariant>

class FileTransfer : public QObject
{
    Q_OBJECT

    Q_PROPERTY (QString fileName        READ fileName)
    Q_PROPERTY (QString userName        READ userName)
    Q_PROPERTY (QString userUuid        READ userUuid)


public:
    enum Roles {
        fileNameRole = Qt::UserRole + 1,
        userNameRole,
        userUuidRole
    };

    FileTransfer(QObject *parent = 0);
    FileTransfer(const QString &userName, const QString &fileName, const QString &userUuid = QString(), QObject *parent = 0);
    ~FileTransfer();

    QVariant data(int role) const;

    QString fileName() const;
    QString userName() const;
    QString userUuid() const;

    bool operator==(const FileTransfer &fileTransfer);

Q_SIGNALS:
    // Don't need update signals at the moment. This type of data doesn't change (for the moment)

private:
    class Private;
    Private * const d;
};

#endif  // USER_H
