#ifndef CONNECTIONCENTER_H
#define CONNECTIONCENTER_H


#include <QtCore/QObject>


/**
 * Used for handling sending and receiving of files from users on the network
 */

class ConnectionCenter : public QObject
{
    Q_OBJECT

public:
    ConnectionCenter(QObject *parent = 0);
    ~ConnectionCenter();

    /**
     * @return the server port the application is listening on
     */
    quint16 serverPort() const;

public Q_SLOTS:
    /**
     * Sends the specified file to the client
     * @param fileName file to send
     * @param ip client ip address to connect to
     * @param port client port to connect to
     */
    void sendFileToClient(const QString &fileName, const QString &ip, int port);

private Q_SLOTS:
    /** handles new connection from clients */
    void onNewConnection();
    void onTransferReceiveJobFinished();

private:
    class Private;
    Private * const d;
};

#endif  // CONNECTIONCENTER_H
