#include <QCoreApplication>
#include "km5device.h"
#include "km5deviceoptions.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    KM5DeviceOptions opts(argc,argv);
    KM5Device dev(opts);
    return a.exec();
}
