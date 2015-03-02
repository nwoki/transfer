#ifndef SYSTRAY_H
#define SYSTRAY_H

#include <QtWidgets/QSystemTrayIcon>

class UserList;


class Systray : public QSystemTrayIcon
{
    Q_OBJECT

public:
    Systray(UserList *userList, QObject *parent = 0);
    ~Systray();

Q_SIGNALS:
    void showSendFileView();

private:
    void prepareMenu();

    class Private;
    Private * const d;
};

#endif  // SYSTRAY_H
