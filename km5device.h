#ifndef KM5DEVICE_H
#define KM5DEVICE_H

#include <QTcpSocket>
#include <km5deviceoptions.h>
#include <QTimer>

class KM5Device : private QTcpSocket
{
    Q_OBJECT
    QTimer tm;
public:
    KM5Device(const KM5DeviceOptions &opts);
    ~KM5Device();
    QTcpSocket sock;
private slots:
    void socketConnected();
    void connectionTimedOut();
};

#endif // KM5DEVICE_H
