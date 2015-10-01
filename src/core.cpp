#include "core.h"
#include "discoverer.h"
#include "settings.h"
#include "systray.h"
#include "userlist.h"
#include "dialogs/settingsdialog.h"

class Core::Private
{
public:
    Private()
        : userList(new UserList)
        , systray(new Systray(userList))
        , discoverer(new Discoverer(userList))
    {}

    UserList *userList;
    Systray *systray;
    Discoverer *discoverer;
};


Core::Core(QObject *parent)
    : QObject(parent)
    , d(new Private)
{
    // setup first run info
    if (Settings::isFirstRun()) {
        // TODO show tutorial in browser?
    }

    // TODO start network magic. This is where the cool part comes into play
    // discovery starts on initialization
}

Core::~Core()
{
    delete d->userList;
    delete d->systray;
    delete d->discoverer;
    delete d;
}

