#ifndef DEVICE_H
#define DEVICE_H


#include <QtCore/QString>

class Device
{
public:
    Device();
    ~Device();

    QString userName() const;
    QString uuid() const;

private:
    class Private;
    Private * const d;
};

#endif  // Device
