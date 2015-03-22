#include "timeinterval.h"
#include "optparser.h"

using namespace OPTPARSER;
using namespace std;


int TimeInterval::check_interval(const int &in)
{
    if(in<0)
    {
        throw invalid_argument("time interval cannot be negative");
    }
    return(in);
}

TimeInterval::TimeInterval(const string &in):value(check_interval(string_to_number<int>(in)))
{

}
