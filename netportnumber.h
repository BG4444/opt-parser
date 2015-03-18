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
        template<typename T> static auto check_range(const T& in)
        {
            if(in < 0)
            {
                throw std::logic_error("port number excesses");
            }
            if(std::numeric_limits<T>::max()>std::numeric_limits<decltype(no)>::max() && in > std::numeric_limits<decltype(no)>::max())
            {
                throw std::logic_error("port number is greather than" +std::to_string(std::numeric_limits<decltype(no)>::max()));
            }
            return(in);
        }

    public:
        const uint16_t no;
        netPortNumber(const std::string& portno);
        virtual ~netPortNumber();
    };
}

#endif // NETPORTNUMBER_H
