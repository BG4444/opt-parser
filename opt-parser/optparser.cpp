#include "optparser.h"
using namespace std;


match_results<const char*> OPTPARSER::g_walk_step(const string& regexString, optlist &args)
{
    if(args.empty())
    {
        return(match_results<const char*>());
    }
#ifndef NDEBUG
        std::cerr << "Regex will be \'"<<regexString<<"\'\n";
#endif
        regex blowarg(regexString);
        for(auto i=args.end();(i--)!=args.begin();)
        {
#ifndef NDEBUG
            std::cerr << "\tParsing an argument \'"<<*i<<'\'';
#endif
            match_results<const char*> matches;
            if(regex_search(*i,matches,blowarg))
            {
#ifndef NDEBUG
               std::cerr << " matches to regex.\n";
#endif
               args.erase(i);
               return(matches);
            }
            else
            {
#ifndef NDEBUG
               std::cerr << " not matches to regex.\n";
#endif
            }
        }
        return(match_results<const char*>());
}

