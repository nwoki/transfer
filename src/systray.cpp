#include "dialogs/settingsdialog.h"
#include "discoverer.h"
#include "filetransferlist.h"
#include "settings.h"
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
        , userList(new UserList)
        , fileTransferList(new FileTransferList)
        , userListView(new QQuickView)
        , discoverer(new Discoverer(userList))
    {
        QDesktopWidget *desktop = QApplication::desktop();

        // set the QML view to the center of the screen
        userListView->setX((desktop->width()/2) - userListView->width()/2);
        userListView->setY((desktop->height()/2) - userListView->height()/2);
    }

    ~Private() {
        qDebug("[Systray::~Private]");

        delete sendFileAction;
        delete settingsAction;
        delete settingsDialog;
        delete discoverer;
        delete fileTransferList;
        delete userList;
        delete userListView;
    }

    QAction *sendFileAction;
    QAction *settingsAction;
    SettingsDialog *settingsDialog;
    UserList *userList;
    FileTransferList *fileTransferList;
    QQuickView *userListView;
    Discoverer *discoverer;
};


Systray::Systray(QObject *parent)
    : QSystemTrayIcon(parent)
    , d(new Private)
{
    // set the user model here. Otherwise I end up with a null ptr. Then, load the qml view file
    d->userListView->rootContext()->setContextProperty("fileTransferListModel", d->fileTransferList);
    d->userListView->rootContext()->setContextProperty("userListModel", d->userList);
    d->userListView->rootContext()->setContextProperty("discoverer", d->discoverer);
    d->userListView->setSource(QUrl("qrc:///qml/main.qml"));

    // When we recieve a "send-file" request
    connect(d->discoverer, &Discoverer::fileTransferRequestReceived, [this] (const QString &fromUser, const QString &fileName, const QString &userUuid) {
        // show notification
        showMessage(tr("Incoming file")
                    , tr("<b>%1</b> wants to send you: <b>\"%2\"</b>    ").arg(fromUser, fileName)
                    , QSystemTrayIcon::Information
                    , 5000);

        d->fileTransferList->addFileTransfer(fromUser, fileName, userUuid);
    });

    connect(d->settingsAction, &QAction::triggered, d->settingsDialog, &QDialog::show);

    connect(this, &QSystemTrayIcon::activated, this, [this] (QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::Trigger) {
            if (d->userListView->isVisible()) {
                d->userListView->hide();
            } else {
                d->userListView->show();
            }
        } else if (reason == QSystemTrayIcon::Context) {
            contextMenu()->show();
        }
    });

    // setup first run info
    if (Settings::isFirstRun()) {
        // TODO show tutorial in browser?
    }

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


