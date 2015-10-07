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
    void sendFileToClient(const QString &clientUuid, const QString &fileName, const QString &ip, int port);

private:
    class Private;
    Private * const d;
};

#endif  // CONNECTIONCENTER_H
