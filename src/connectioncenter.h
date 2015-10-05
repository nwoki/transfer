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

private:
    class Private;
    Private * const d;
};

#endif  // CONNECTIONCENTER_H
