#include "timeinterval.h"
#include "optparser.h"

using namespace OPTPARSER;
using namespace std;


TimeInterval::TimeInterval(const string &in):value(squeeze_range_positive<int>(stoul(in),"session time"))
{

}
