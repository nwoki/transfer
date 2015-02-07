#ifndef USER_H
#define USER_H


#include <QtCore/QString>

class User
{
public:
    User();
    User(const QString &userName, const QString &uuid);
    ~User();

    QString userName() const;
    QString uuid() const;

private:
    class Private;
    Private * const d;
};

#endif  // USER_H
