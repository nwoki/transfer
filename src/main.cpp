#include "core.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationDisplayName("Transfer");
    a.setApplicationName("Transfer");
    a.setOrganizationName("nwoki");

    Core core;

    return a.exec();
}
