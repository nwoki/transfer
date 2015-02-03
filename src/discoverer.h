#ifndef DISCOVERER_H
#define DISCOVERER_H

#include <QtCore/QObject>

#include <QtNetwork/QAbstractSocket>


/**
 * Class in charge of detecting other available nodes (other computers
 * with the Transfer app running) and advertising itself for others to know about
 */

class Discoverer : public QObject
{
    Q_OBJECT

public:
    Discoverer(QObject *parent = 0);
    ~Discoverer();

private Q_SLOTS:
    void advertise();
    void onError(QAbstractSocket::SocketError socketError);

private:
    class Private;
    Private * const d;
};

#endif  // DISCOVERER_H
