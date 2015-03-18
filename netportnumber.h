#ifndef NETPORTNUMBER_H
#define NETPORTNUMBER_H
#include <string>
#include <QtNetwork>

namespace OPTPARSER
{
    class netPortNumber
    {
        template<typename T> static quint16 check_range(const T& in)
        {
            if(in < 0)
            {
                throw std::logic_error("port number excesses");
            }
            if(std::numeric_limits<T>::max()>std::numeric_limits<decltype(no)>::max() && in > std::numeric_limits<decltype(no)>::max())
            {
                throw std::logic_error("port number excesses");
            }
            return(in);
        }

    public:
        const quint16 no;
        netPortNumber(const std::string& portno);
        virtual ~netPortNumber();
    };
}

#endif // NETPORTNUMBER_H
