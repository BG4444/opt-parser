#include <QCoreApplication>
#include "km5device.h"
#include "km5deviceoptions.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    KM5DeviceOptions opts(argc,argv);
    cerr<<hex<<$(opts,"deviceID").id<<' '<<dec<<$(opts,"deviceID").id<<endl;
    KM5Device dev(opts);
    return a.exec();
}
