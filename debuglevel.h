#ifndef DEBUGLEVEL_H
#define DEBUGLEVEL_H

namespace OPTPARSER
{
    template<typename T>  class DebugLevel
    {
        static T makeLVL(const uint8_t in)
        {
            if(in<=4)
            {
                return static_cast<T>(in);
            }
            throw std::invalid_argument("debug level exceeds maximum!");
        }
    public:
        const T lvl;
        DebugLevel(const std::string& in):
            lvl(makeLVL(string_to_number<uint8_t>(in)))
        {
        }
        operator T() const
        {
            return lvl;
        }
        virtual ~DebugLevel(){};
    };
}
#endif // DEBUGLEVEL_H
