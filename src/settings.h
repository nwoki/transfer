#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore/QString>

class Settings
{
public:
    static QString downloadDir();
    /**
     * checks settings file to see if the application is being launched
     * for the first time. If so, prompt the user with:
     * ~ web page with tutorial? TODO
     * ~ settings dialog
     */
    static bool isFirstRun();
    static QString username();
    static QString uuid();

private:
    static void resetUuid();

};

#endif  // SETTINGS_H
