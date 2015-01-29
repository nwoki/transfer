#include "settings.h"

#include <QtCore/QSettings>
#include <QtCore/QStandardPaths>

#include <QtNetwork/QHostInfo>

bool Settings::isFirstRun()
{
    bool firstRun = false;
    QSettings settings;

    // check we have some values. If non exist, set default info
    if (settings.value("user/name").toString().isEmpty()) {
        settings.setValue("user/name", QHostInfo::localHostName());
        settings.setValue("user/download_dir", QStandardPaths::writableLocation(QStandardPaths::DownloadLocation));
        settings.sync();

        firstRun = true;
    }

    return firstRun;
}
