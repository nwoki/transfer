#ifndef CORE_H
#define CORE_H

#include <QtCore/QObject>

class Core : public QObject
{
    Q_OBJECT

public:
    Core(QObject *parent = 0);
    ~Core();

private:
    /**
     * checks settings file to see if the application is being launched
     * for the first time. If so, prompt the user with:
     * ~ web page with tutorial? TODO
     * ~ settings dialog
     */
//     void checkFirstRun();

    class Private;
    Private const * d;
};

#endif  // CORE_H
