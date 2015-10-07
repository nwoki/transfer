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
     * Accepts a pending file transfer request
     * @param uuid the uuid of the client that wants to send us the file
     * @param fileName the name of the file to give the "ok" for
     */
    Q_INVOKABLE void acceptFileTransfer(const QString &uuid, const QString &fileName);

    /**
     * Shows a QFileDialog from which the user chooses a file to send to the selected
     * user. Once the file is selected, a "send" request is sent to that user. If the request returns "true"
     * then the transfer begins. Otherwise the transfer is dropped.
     *
     * @param uuid uuid of the user to send the file to
     */
    Q_INVOKABLE void sendFileToUser(const QString &uuid);

private Q_SLOTS:
    void advertise();
    void onError(QAbstractSocket::SocketError socketError);
    void onFileTransferAccepted(const QString &fromUuid, const QString &fileName, const QString &ip, int port);


Q_SIGNALS:
    void fileTransferRequestReceived(const QString &fromUser, const QString &fileName, const QString &userUuid);

    // TODO not used
    /**
     * signal that tells the application we want to send a file to a user
     *
     * @param destinationUserUuid uuid of the user we want to send the file to
     * @param filePath path to the file we want to send
     */
//     void sendFile(const QString &destinationUserUuid, const QString &filePath);

private:
    class Private;
    Private * const d;
};

#endif  // DISCOVERER_H
