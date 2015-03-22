#ifndef KM5DEVICEOPTIONS_H
#define KM5DEVICEOPTIONS_H

#include "km5device.h"
#include "opt-parser/optparser.h"
#include "opt-parser/netportnumber.h"
#include <QHostAddress>

struct optlist
{
    static constexpr auto options=tuple_cat(
                OPTPARSER::makeO<OPTPARSER::netPortNumber>("port"),
                OPTPARSER::makeO<QHostAddress>("inaddr")
                );

};

class KM5DeviceOptions: public OPTPARSER::Options<optlist>
{
public:
    KM5DeviceOptions(int argc,char* argv[]);
    ~KM5DeviceOptions();
};

#endif // KM5DEVICEOPTIONS_H
