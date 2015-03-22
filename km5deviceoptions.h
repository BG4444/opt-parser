#ifndef KM5DEVICEOPTIONS_H
#define KM5DEVICEOPTIONS_H


#include "opt-parser/optparser.h"
#include "opt-parser/netportnumber.h"
#include <QHostAddress>
#include "opt-parser/timeinterval.h"

class deviceID
{
public:
    const uint32_t id;
    deviceID(const std::string& in):id(OPTPARSER::string_to_number<uint32_t>(in))
    {

    }
};

struct optlist
{
    static constexpr auto options=tuple_cat(
                OPTPARSER::makeO<OPTPARSER::netPortNumber>("port"),
                OPTPARSER::makeO<QHostAddress>("host"),
                OPTPARSER::makeO("connectionTimeout",[](){return OPTPARSER::TimeInterval(5000);}),
                OPTPARSER::makeO<deviceID>("deviceID")
                );

};


class KM5DeviceOptions: public OPTPARSER::Options<optlist>
{
public:
    KM5DeviceOptions(int argc,char* argv[]);
    ~KM5DeviceOptions();
};

#endif // KM5DEVICEOPTIONS_H
