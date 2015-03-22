#ifndef KM5DEVICE_H
#define KM5DEVICE_H

#include <QTcpSocket>

class KM5Device : private QTcpSocket
{
    Q_OBJECT
public:
    KM5Device();
    ~KM5Device();
};

#endif // KM5DEVICE_H
