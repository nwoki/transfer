#include "settings.h"

#include <QtCore/QSettings>

#include <QtNetwork/QHostInfo>

bool Settings::isFirstRun()
{
    bool firstRun = false;
    QSettings settings;

    // check we have some values. If non exist, set default info
    if (settings.value("user/name").toString().isEmpty()) {
        settings.setValue("user/name", QHostInfo::localHostName());

        firstRun = true;
    }

    return firstRun;
}
