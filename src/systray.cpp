#include "systray.h"

#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>

class Systray::Private
{
public:
    Private()
        : sendFileAction(new QAction(tr("Send&File"), nullptr))
        , settingsAction(new QAction(tr("&Settings"), nullptr))
    {};

    QAction *sendFileAction;
    QAction *settingsAction;
};


Systray::Systray(QObject *parent)
    : QSystemTrayIcon(parent)
    , d(new Private)
{
    setIcon(QIcon(":/images/icons/tray_icon.png"));
    prepareMenu();
    setVisible(true);
}


Systray::~Systray()
{
    delete d->sendFileAction;
    delete d->settingsAction;
    delete d;
}

void Systray::prepareMenu()
{
    QMenu *contextMenu = new QMenu;

    contextMenu->addAction(d->sendFileAction);
    contextMenu->addAction(d->settingsAction);

    setContextMenu(contextMenu);
}





