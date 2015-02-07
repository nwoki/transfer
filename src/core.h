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
    class Private;
    Private * const d;
};

#endif  // CORE_H
