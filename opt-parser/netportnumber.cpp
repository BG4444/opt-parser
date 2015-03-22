#include "netportnumber.h"
#include "optparser.h"

using namespace OPTPARSER;
using namespace std;

netPortNumber::netPortNumber(const string &portno):no(string_to_number<std::remove_const<decltype(no)>::type>(portno))
{

}

netPortNumber::~netPortNumber()
{

}

