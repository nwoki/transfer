#ifndef USER_H
#define USER_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>

class User : public QObject
{
    Q_OBJECT

    Q_PROPERTY (bool selected           READ isSelected         NOTIFY userDataChanged)
    Q_PROPERTY (QString userName        READ userName)
    Q_PROPERTY (QString uuid            READ uuid)

public:
    enum Roles {
        selectedRole = Qt::UserRole + 1,
        userNameRole,
        uuidRole
    };

    User(QObject *parent = 0);
    User(const QString &userName, const QString &uuid);
    ~User();

    QVariant data(int role) const;

    bool isSelected() const;

    /** toggles the user selected flag (used for file transfers) */
    void toggleSelected();

    QString userName() const;
    QString uuid() const;

    bool operator==(const User &user);

Q_SIGNALS:
    void userDataChanged();

private:
    class Private;
    Private * const d;
};

#endif  // USER_H
