#ifndef PARSER_H
#define PARSER_H

#include <QtCore/QObject>

class Parser : public QObject
{
    Q_OBJECT

public:
    Parser(QObject *parent = 0);
    ~Parser();

    void parse(const QByteArray &data);

Q_SIGNALS:
    void fileTransferRequest(const QString &fromUser, const QString &fileName, const QString &userUuid);
    void userDiscovered(const QString &userName, const QString &uuid);

private:
    class Private;
    Private * const d;
};

#endif  // PARSER_H
