#include "device.h"

class Device::Private
{
public:
    Private() {}

    QString username;
    QString uuid;
};


Device::Device()
    : d(new Private)
{
}

Device::~Device()
{
    delete d;
}

QString Device::userName() const
{
    return d->username;
}

QString Device::uuid() const
{
    return d->uuid;
}
