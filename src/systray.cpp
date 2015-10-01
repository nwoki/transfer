#include "dialogs/settingsdialog.h"
#include "systray.h"
#include "userlist.h"

#include <QtCore/QDebug>

#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QMenu>

#include <QtQml/QQmlContext>

#include <QtQuick/QQuickView>

class Systray::Private
{
public:
    Private()
        : sendFileAction(new QAction(QIcon(":/images/icons/arrow-up-double.png"), tr("Send&File"), nullptr))
        , settingsAction(new QAction(QIcon(":/images/icons/configure.png"), tr("&Settings"), nullptr))
        , settingsDialog(new SettingsDialog)
        , userList(nullptr)
        , sendFileView(new QQuickView)
    {
        QDesktopWidget *desktop = QApplication::desktop();

        // set the QML view to the center of the screen
        sendFileView->setX((desktop->width()/2) - sendFileView->width()/2);
        sendFileView->setY((desktop->height()/2) - sendFileView->height()/2);
    }

    ~Private() {
        qDebug("[Systray::~Private]");

        delete sendFileAction;
        delete settingsAction;
        delete settingsDialog;
        delete sendFileView;
    }

    QAction *sendFileAction;
    QAction *settingsAction;
    SettingsDialog *settingsDialog;
    UserList *userList;
    QQuickView *sendFileView;
};


Systray::Systray(UserList *userList, QObject *parent)
    : QSystemTrayIcon(parent)
    , d(new Private)
{
    d->userList = userList;

    // set the user model here. Otherwise I end up with a null ptr. Then, load the qml view file
    d->sendFileView->rootContext()->setContextProperty("userListModel", d->userList);
    d->sendFileView->setSource(QUrl("qrc:///qml/sendfile/main.qml"));

    connect(d->sendFileAction, &QAction::triggered, d->sendFileView, &QQuickView::show);
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





