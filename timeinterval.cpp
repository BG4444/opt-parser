#include "timeinterval.h"
#include "optparser.h"

using namespace OPTPARSER;
using namespace std;


TimeInterval::TimeInterval(const string &in):value(string_to_number<int>(in))
{

}
