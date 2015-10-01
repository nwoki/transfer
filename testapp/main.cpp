#include "commanddispatcher.h"

#include <QtCore/QCommandLineParser>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QStringList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CommandDispatcher cmdDispatcher(5555);

    QCommandLineParser parser;
    parser.addHelpOption();

    parser.addOptions({
        // Boolean option for advertising
        {{"a", "advertise"}, QCoreApplication::translate("advertise", "Advertises itself on the LAN")}

//         // A boolean option with a single name (-p)
//         {"p", QCoreApplication::translate("main", "Show progress during copy")}
//
//         // A boolean option with multiple names (-f, --force)
//         ,{{"f", "force"}, QCoreApplication::translate("main", "Overwrite existing files.")}
//
//         // An option with a value
//         ,{{"t", "target-directory"}, QCoreApplication::translate("main", "Copy all source files into <directory>."), QCoreApplication::translate("main", "directory")},
    });


//     parser.process(a);


    parser.parse(QCoreApplication::arguments());

    qDebug() << "OPTION: " << parser.isSet("a");

    if (parser.isSet("a")) {
        cmdDispatcher.advertise();
    }

    return a.exec();
}
