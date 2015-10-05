#ifndef USERLIST_H
#define USERLIST_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QString>


class User;

/**
 * Class used to keep track of users on the LAN and to provide a
 * model of these users when needed
 */

class UserList : public QAbstractListModel
{
    Q_OBJECT

public:
    UserList(QObject *parent = 0);
    ~UserList();

    QHash<int, QByteArray> roleNames() const;

    /**
     * @param uuid uuid of the user we want
     * @return a pointer to the user requested.
     */
    Q_INVOKABLE QObject *user(const QString &uuid);

    /**
     * Shows a QFileDialog from which the user chooses a file to send to the selected
     * user.
     *
     * @param uuid uuid of the user to send the file to
     */
    Q_INVOKABLE void sendFileToUser(const QString &uuid);

    // DEPRECATED
    /**
     * toggles the "selected" status of the specified user
     * @param uuid uuid of the user to toggle the selection of
     */
    Q_INVOKABLE void toggleSelected(const QString &uuid);

    // TODO user selected status reset

public Q_SLOTS:
    /**
     * Adds a user to the list model
     *
     * @param userName user's username
     * @param uuid user's uuid
     */
    void addUser(const QString &userName, const QString &uuid);

Q_SIGNALS:
    /**
     * signal that tells the application we want to send a file to a user
     *
     * @param destinationUserUuid uuid of the user we want to send the file to
     * @param filePath path to the file we want to send
     */
    void sendFile(const QString &destinationUserUuid, const QString &filePath);

private:
    void addUserToModel(User *user);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &index = QModelIndex()) const;

    class Private;
    Private * const d;
};


#endif  // USERLIST_H
