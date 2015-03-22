#ifndef TIMEINTERVAL_H
#define TIMEINTERVAL_H
#include <string>
#include <limits>

namespace OPTPARSER
{
    class TimeInterval
    {
        static int check_interval(const int& in);
    public:
        TimeInterval(const std::string& in);
        TimeInterval(const int &in);
        const int value;
    };
}
#endif // TIMEINTERVAL_H
