#ifndef TRANSFERRECEIVEJOB_H
#define TRANSFERRECEIVEJOB_H

#include <QtCore/QObject>

class QTcpSocket;

/**
 * A worker class that handles the download of an incoming file
 * sent from a remote peer
 */
class TransferReceiveJob : public QObject
{
    Q_OBJECT

public:
    TransferReceiveJob(QTcpSocket *peerConnection, QObject *parent = 0);
    ~TransferReceiveJob();

Q_SIGNALS:
    void finished();

private Q_SLOTS:
    void onReadyRead();

private:
    void saveDataToFile(const QByteArray &data);
    void sendAck();

    class Private;
    Private * const d;
};

#endif  // TRANSFERRECEIVEJOB_H
