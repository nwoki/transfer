#ifndef TRANSFERSENDJOB_H
#define TRANSFERSENDJOB_H

#include <QtCore/QObject>

class QTcpSocket;

/**
 * A worker class that handles the sending of a file to be
 * sent to a remote peer
 */
class TransferSendJob : public QObject
{
    Q_OBJECT

public:
    TransferSendJob(const QString &fileName, const QString &peerAddress, int peerPort, QObject *parent = 0);
    ~TransferSendJob();

    void startTransfer();

Q_SIGNALS:
    void finished(bool success, const QString &errorMsg = QString());

private Q_SLOTS:
    void onConnected();
    void onDisconnected();
    void onReadyRead();

private:
    void sendFile();

    class Private;
    Private * const d;
};

#endif  // TRANSFERSENDJOB_H
