#include "netportnumber.h"
#include "optparser.h"

using namespace OPTPARSER;
using namespace std;

netPortNumber::netPortNumber(const string &portno):no(squeeze_range_positive<std::remove_const<decltype(no)>::type>(stoul(portno),"port name"))
{

}

netPortNumber::~netPortNumber()
{

}

