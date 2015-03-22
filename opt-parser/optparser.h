#ifndef OPTPARSER_H
#define OPTPARSER_H

#include <tuple>
#include <assert.h>
#include <regex>
#include <iostream>
#include <list>

namespace OPTPARSER
{

    template<typename OUT> OUT do_convert_dec(std::string::const_iterator beg,const std::string::const_iterator& en)
    {
        static_assert( std::numeric_limits<OUT>::max()>=10,"not enough space in type");

        OUT ret=0;
        const OUT ten(10);
        const OUT rmax(std::numeric_limits<OUT>::max()/ten);


        for(;beg!=en;++beg)
        {
            if(*beg<'0' || *beg>'9')
            {
                throw std::invalid_argument("wrong symbol found");
            }
            const OUT digit=*beg-'0';
            if( ret > rmax)
            {
                throw std::invalid_argument("overflow on shift");
            }
            ret*=ten;
            if( ret > std::numeric_limits<OUT>::max()-digit)
            {
                throw std::invalid_argument("overflow on add");
            }
            ret+=digit;

        }
        return(ret);
    }

    template<typename OUT> OUT do_convert_hex(std::string::const_iterator beg,const std::string::const_iterator& en)
    {
        static_assert( std::numeric_limits<OUT>::max()>=16,"not enough space in type");

        OUT ret=0;
        const OUT sixteen(16);
        const OUT rmax(std::numeric_limits<OUT>::max()/sixteen);


        for(;beg!=en;++beg)
        {
            OUT digit;
            if  (*beg>='0' && *beg<='9')
            {
                digit=*beg-'0';
            }
            else
            {
                if(*beg>='A' && *beg<='F')
                {
                    digit=*beg-'A';
                }
                else
                {
                    throw std::invalid_argument("wrong symbol found");
                }
            }

            if( ret > rmax)
            {
                throw std::invalid_argument("overflow on shift");
            }
            ret*=sixteen;
            if( ret > std::numeric_limits<OUT>::max()-digit)
            {
                throw std::invalid_argument("overflow on add");
            }
            ret+=digit;
        }
        return(ret);
    }

    template<typename OUT,bool sign> struct string_conversions
    {
    };

    template<typename OUT> struct string_conversions<OUT,true>
    {        
        static OUT do_convert(std::string::const_iterator beg,const std::string::const_iterator& en)
        {
            static_assert( std::numeric_limits<OUT>::min()<=-9,"not enough space in type");
            static_assert( std::numeric_limits<OUT>::max()>=10, "not enough space in type");
            switch(*beg)
            {
                case '-':
                {                            
                    if(++beg==en)
                    {
                        throw std::invalid_argument("this string is not a number");
                    }
                    OUT ret=0;
                    const OUT ten(10);
                    const OUT rmin((std::numeric_limits<OUT>::min()/ten));
                    for(;beg!=en;++beg)
                    {
                        if(*beg<'0' || *beg>'9')
                        {
                            throw std::invalid_argument("wrong symbol found");
                        }
                        const OUT digit=*beg-'0';
                        if( ret < rmin)
                        {
                            throw std::invalid_argument("overflow on shift");
                        }
                        ret*=ten;
                        if(ret <  std::numeric_limits<OUT>::min()+digit)
                        {
                            throw std::invalid_argument("overflow on add");
                        }
                        ret-=digit;

                    }
                    return(ret);
                }
                case '+':
                {                            
                    if(++beg==en)
                    {
                        throw std::invalid_argument("this string is not a number");
                    }
                }
                default:
                {
                    return(string_conversions<OUT,false>::do_convert(beg,en));
                }
            }
        }
    };

    template<typename OUT> struct string_conversions<OUT,false>
    {        
        static OUT do_convert(std::string::const_iterator beg,const std::string::const_iterator& en)
        {
            if(*beg=='0')
            {
                if(++beg==en)
                {
                    return 0;
                }
                if(*beg=='x')
                {
                    if(++beg==en)
                    {
                        throw std::invalid_argument("this string is not a number");
                    }
                    return(do_convert_hex<OUT>(beg,en));
                }
            }
            return(do_convert_dec<OUT>(beg,en));
        }
    };

    template<typename OUT> static OUT string_to_number(const std::string& value)
    {
        static_assert( std::numeric_limits<OUT>::is_exact,"not exact type");
        if(value.empty())
        {
            throw std::invalid_argument("empty string is given!");
        }
        return(string_conversions<OUT,std::numeric_limits<OUT>::is_signed>::do_convert(value.cbegin(),value.cend()));
    }

    using optlist=std::list<const char*>;

    template<typename T> struct NoDefaultValue
    {
    };

    template<typename T> struct HasDefaultValue
    {
    };

    struct Boolean
    {
    };

    template <typename T>
    struct function_traits
        : public function_traits<decltype(&T::operator())>
    {};
    // For generic types, directly use the result of the signature of its 'operator()'

    template <typename ClassType, typename ReturnType, typename... Args>
    struct function_traits<ReturnType(ClassType::*)(Args...) const>
    // we specialize for pointers to member function
    {
        typedef ReturnType result_type;
    };

    constexpr auto makeO(const char* name,bool defvalue=false)
    {
        return std::make_tuple(name,Boolean(),defvalue);
    }


    template<typename T> constexpr auto makeO(const char* name,T dflMaker)
    {
        typedef function_traits<T> traits;
        typedef typename traits::result_type parameter_type;

        return std::make_tuple(name,HasDefaultValue<parameter_type>(),dflMaker);
    }

    template<typename T> constexpr auto makeO(const char* name)
    {
        return std::make_tuple(name,NoDefaultValue<T>(),nullptr);
    }


    constexpr size_t scomp(const char* a,const char* b)
    {
        return( (*a==*b)
                ? (
                          (*a=='\0')
                          ? 1
                          : scomp(a+1,b+1)
                  )
                : 0
              );
    }

    std::match_results<const char *> g_walk_step(const std::string& regexString,optlist& args);

    template<typename T,typename Initializer> struct walker_step
    {
    };

    template<> struct walker_step<const Boolean,const bool >
    {
        static auto walk_step(const char* name,const bool init,optlist& args)                    //rfirst       init   out
        {                                                                                        //   0           0     1
                const auto res=g_walk_step(std::string("--") + std::string(name),args);          //   0           1     0
                return(std::make_tuple(init==res.empty()));                                      //   1           0     0
        }                                                                                        //   1           1     1
        static constexpr auto slice_step()
        {
            return std::make_tuple(bool());
        }
    };

    template<typename T,typename Initializer> struct walker_step<const HasDefaultValue<T>,Initializer >
    {
        static auto walk_step(const char* name,Initializer init,optlist& args)
        {
                const auto res=g_walk_step(std::string("--") + std::string(name) + ("=(.*)"),args);
                if(res.empty())
                {
                    return(std::make_tuple(init()));
                }
                else
                {
                    assert(res.size()==2);
                    return(std::make_tuple(T(res[1])));
                }

        }
        static constexpr auto slice_step()
        {
            return std::make_tuple(T(""));
        }
    };

    template<typename T,typename Initializer> struct walker_step <const NoDefaultValue<T>, Initializer >
    {
        static auto walk_step(const char* name,Initializer,optlist &args)
        {
            const auto res=g_walk_step(std::string("--") + std::string(name) + ("=(.*)"),args);
            if(res.empty())
            {
                throw std::logic_error("Mandatory parameter is not set!");
            }
            else
            {
                assert(res.size()==2);
    #ifndef NDEBUG
                std::cerr << "\t\tArgument is " << res[1] <<'\n';
    #endif
                return(std::make_tuple(T(res.str(1).c_str())));
            }
        }
        static constexpr auto slice_step()
        {
            return std::make_tuple(T(""));
        }
    };


    template<typename A,size_t N> struct walker
    {
        static constexpr size_t find(A input,const char* func)
        {
            return(
                        (scomp(std::get<N>(input),func)==1)
                            ? (N)
                            : walker<A,N-3>::find(input,func)
                  );
        }
        static constexpr auto walk(A input,optlist& args)
        {
            return tuple_cat(
                        walker<A,N-3>::walk(input,args),
                         walker_step<typename std::tuple_element<N+1,A>::type,typename std::tuple_element<N+2,A>::type>::walk_step(std::get<N>(input),std::get<N+2>(input),args)
                        );
        }
      static constexpr auto slice(A input)
        {
            return tuple_cat(
                        walker<A,N-3>::slice(input),
                         walker_step<typename std::tuple_element<N+1,A>::type,typename std::tuple_element<N+2,A>::type>::slice_step()
                       );
        }
        static constexpr bool checkDupes(A input)
        {
            return (walker<A,N-3>::find(input,std::get<N>(input))!=size_t(-1)) | walker<A,N-3>::checkDupes(input);
        }
    };

    template<typename A> struct walker<A,0>
    {
        static constexpr size_t find(A input,const char* func)
        {
            return(
                          (scomp(std::get<0>(input),func)==1)
                          ?  0
                          :   -1
                  );
        }
        static constexpr auto walk(A input,optlist& args)
        {
            return walker_step<typename std::tuple_element<1,A>::type,typename std::tuple_element<2,A>::type>::walk_step(std::get<0>(input),std::get<2>(input),args);
        }
        static constexpr auto slice(A)
        {
            return walker_step<typename std::tuple_element<1,A>::type,typename std::tuple_element<2,A>::type>::slice_step();
        }
        static constexpr bool checkDupes(A)
        {
            return false;
        }
    };


    template<bool check> class OptionsCheck
    {
        static constexpr bool chk()
        {
            static_assert(!check,"duplicate options found!");
            return(true);
        }
        static constexpr auto checked=chk();
    public:
        virtual ~OptionsCheck()
        {

        }
    };

    template<class Cont> class Options :private OptionsCheck< walker<decltype(Cont::options),std::tuple_size<decltype(Cont::options)>::value-3>::checkDupes(Cont::options) >
    {
    public:
        optlist residue_args;
    private:

        decltype(walker<decltype(Cont::options),std::tuple_size<decltype(Cont::options)>::value-3>::slice(Cont::options)) vals;

        static size_t check_argc(int argc)
        {
            if(argc<0)
            {
                throw std::logic_error("Negative parameter count!");
            }
            return argc;
        }

    public:
        Options(int argc,char* argv[]):residue_args(&argv[1],&argv[check_argc(argc)]),vals(walker<decltype(Cont::options),std::tuple_size<decltype(Cont::options)>::value-3>::walk(Cont::options,residue_args))
        {

        }
        static constexpr size_t find(const char* func)
        {
            return walker<decltype(Cont::options),std::tuple_size<decltype(Cont::options)>::value-3>::find(Cont::options,func);
        }
        template<size_t index> const auto& extract() const
        {
            static_assert(index!=size_t(-1),"err not found");
            return std::get<index/3>(vals);
        }
        template<size_t index> auto& extract()
        {
            static_assert(index!=size_t(-1),"err not found");
            return std::get<index/3>(vals);
        }
    };
}

#define $(optlist,name) ((optlist).extract<(optlist).find(name)>())

#endif // OPTPARSER_H
