#ifndef NETPORTNUMBER_H
#define NETPORTNUMBER_H
#include <string>
#include <inttypes.h>
#include <stdexcept>
#include <limits>

namespace OPTPARSER
{
    class netPortNumber
    {
    public:
        const int16_t no;
    private:

    public:
        netPortNumber(const std::string& portno);

        virtual ~netPortNumber();
    };
}

#endif // NETPORTNUMBER_H
