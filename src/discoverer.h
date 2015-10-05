#ifndef DISCOVERER_H
#define DISCOVERER_H

#include <QtCore/QObject>

#include <QtNetwork/QAbstractSocket>

class UserList;

/**
 * Class in charge of detecting other available nodes (other computers
 * with the Transfer app running) and advertising itself for others to know about
 */

class Discoverer : public QObject
{
    Q_OBJECT

public:
    Discoverer(UserList *userlist, QObject *parent = 0);
    ~Discoverer();

    /**
     * Shows a QFileDialog from which the user chooses a file to send to the selected
     * user.
     *
     * @param uuid uuid of the user to send the file to
     */
    Q_INVOKABLE void sendFileToUser(const QString &uuid);

private Q_SLOTS:
    void advertise();
    void onError(QAbstractSocket::SocketError socketError);


Q_SIGNALS:
    /**
     * signal that tells the application we want to send a file to a user
     *
     * @param destinationUserUuid uuid of the user we want to send the file to
     * @param filePath path to the file we want to send
     */
    void sendFile(const QString &destinationUserUuid, const QString &filePath);

private:
    class Private;
    Private * const d;
};

#endif  // DISCOVERER_H
