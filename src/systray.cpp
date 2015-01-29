#include "dialogs/settingsdialog.h"
#include "systray.h"

#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>

class Systray::Private
{
public:
    Private()
        : sendFileAction(new QAction(tr("Send&File"), nullptr))
        , settingsAction(new QAction(tr("&Settings"), nullptr))
        , settingsDialog(new SettingsDialog)
    {};

    ~Private() {
        delete sendFileAction;
        delete settingsAction;
        delete settingsDialog;
    }

    QAction *sendFileAction;
    QAction *settingsAction;

    SettingsDialog *settingsDialog;
};


Systray::Systray(QObject *parent)
    : QSystemTrayIcon(parent)
    , d(new Private)
{
//     connect(d->sendFileAction, &QAction::triggered, d->sendFileDialog, &QDialog::show);
    connect(d->settingsAction, &QAction::triggered, d->settingsDialog, &QDialog::show);

    setIcon(QIcon(":/images/icons/tray_icon.png"));
    prepareMenu();
    setVisible(true);
}


Systray::~Systray()
{
    delete d;
}

void Systray::prepareMenu()
{
    QMenu *contextMenu = new QMenu;

    contextMenu->addAction(d->sendFileAction);
    contextMenu->addAction(d->settingsAction);

    setContextMenu(contextMenu);
}





