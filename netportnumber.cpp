#include "netportnumber.h"

using namespace OPTPARSER;
using namespace std;

netPortNumber::netPortNumber(const string &portno):no(check_range(stoul(portno)))
{

}

netPortNumber::~netPortNumber()
{

}

