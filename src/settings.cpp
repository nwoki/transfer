#include "settings.h"

#include <QtCore/QSettings>
#include <QtCore/QStandardPaths>
#include <QtCore/QUuid>

#include <QtNetwork/QHostInfo>

QString Settings::downloadDir()
{
    QSettings settings;
    return settings.value("user/download_dir").toString();
}

bool Settings::isFirstRun()
{
    bool firstRun = false;
    QSettings settings;

    // check we have some values. If non exist, set default info
    if (settings.value("user/name").toString().isEmpty()) {
        settings.setValue("user/name", QHostInfo::localHostName());
        settings.setValue("user/download_dir", QStandardPaths::writableLocation(QStandardPaths::DownloadLocation));
        settings.setValue("user/uuid", uuid());
        settings.sync();

        firstRun = true;
    }

    return firstRun;
}

void Settings::resetUuid()
{
    QSettings settings;
    settings.setValue("user/uuid", QUuid::createUuid().toString().replace("{","").replace("}",""));
    settings.sync();
}

QString Settings::username()
{
    QSettings settings;
    return settings.value("user/name").toString();
}

QString Settings::uuid()
{
    QSettings settings;
    QString uuid = settings.value("user/uuid").toString();

    if (uuid.isEmpty()) {
        resetUuid();
    }

    return settings.value("user/uuid").toString();
}


