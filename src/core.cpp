#include "core.h"
#include "settings.h"
#include "dialogs/settingsdialog.h"
#include "systray.h"

class Core::Private
{
public:
    Private()
        : systray(new Systray)
    {}

    Systray *systray;
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
}

Core::~Core()
{
    delete d->systray;
    delete d;
}

