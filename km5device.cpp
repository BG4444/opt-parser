#include "km5device.h"

KM5Device::KM5Device(const KM5DeviceOptions &opts)
{
    tm.setSingleShot(true);
    assert(connect(&tm,SIGNAL(timeout()),this,SLOT(connectionTimedOut())));
    assert(connect(&sock,SIGNAL(connected()),this,SLOT(socketConnected())));
    tm.start($(opts,"connectionTimeout").value);
    sock.connectToHost($(opts,"host"),$(opts,"port").no);
}

KM5Device::~KM5Device()
{

}

void KM5Device::socketConnected()
{

}

void KM5Device::connectionTimedOut()
{
    throw std::logic_error("connection timed out");
}

