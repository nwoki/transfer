#include "systray.h"


class Systray::Private
{
public:
    Private() {};
};


Systray::Systray(QObject *parent)
    : QSystemTrayIcon(parent)
    , d(new Private)
{
    setIcon(QIcon(":/images/icons/tray_icon.png"));
    setVisible(true);
}


Systray::~Systray()
{
    delete d;
}




