#ifndef SYSTRAY_H
#define SYSTRAY_H

#include <QtWidgets/QSystemTrayIcon>


/**
 * Main obejct of the application. This can be considered the core of the program. It holds all
 * the pieces together and gets them communicating one with another.
 * Plus, it's the main GUI object
 */

class Systray : public QSystemTrayIcon
{
    Q_OBJECT

public:
    Systray(QObject *parent = 0);
    ~Systray();

private:
    void prepareMenu();

    class Private;
    Private * const d;
};

#endif  // SYSTRAY_H
