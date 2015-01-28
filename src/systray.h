#ifndef SYSTRAY_H
#define SYSTRAY_H

#include <QtWidgets/QSystemTrayIcon>


class Systray : public QSystemTrayIcon
{
    Q_OBJECT

public:
    Systray(QObject *parent = 0);
    ~Systray();

private:
    void prepareMenu();

    class Private;
    Private const * d;
};

#endif  // SYSTRAY_H
