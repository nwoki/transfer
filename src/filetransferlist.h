#ifndef FILETRANSFERLIST_H
#define FILETRANSFERLIST_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QList>
#include <QtCore/QString>


class FileTransfer;

/**
 * Class used to keep track of the pending file transfers and provide a
 * model of these
 */

// TODO add id to fileTransfer if needed


class FileTransferList : public QAbstractListModel
{
    Q_OBJECT

public:
    FileTransferList(QObject *parent = 0);
    ~FileTransferList();

    QHash<int, QByteArray> roleNames() const;

    /**
     * @param uuid uuid of the user we want
     * @return a pointer to the user requested.
     */
//     Q_INVOKABLE QObject *fileTransfer(const QString &uuid);


public Q_SLOTS:
    /**
     * Adds a user to the list model
     *
     * @param userName user's username
     * @param fileName name of the file to receive
     * @param userUuid incoming user's uuid
     */
    void addFileTransfer(const QString &userName, const QString &fileName, const QString &userUuid);

private:
    void addFileTransferToModel(FileTransfer *user);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &index = QModelIndex()) const;

    class Private;
    Private * const d;
};


#endif  // FILETRANSFERLIST_H
