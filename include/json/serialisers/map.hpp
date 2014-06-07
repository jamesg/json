#ifndef JSON_SERIALISERS_MAP_HPP
#define JSON_SERIALISERS_MAP_HPP

#include <map>
#include <ostream>
#include <string>

namespace json
{
    template <typename FuncA, typename FuncB, typename K, typename V>
    void serialise(
            const std::map<K, V> &,
            FuncA,
            FuncB,
            std::string,
            std::string,
            std::ostream & );
}

template <typename FuncA, typename FuncB, typename K, typename V>
void json::serialise(
        const std::map<K, V> &m,
        FuncA fa,
        FuncB fb,
        std::string ms,
        std::string is,
        std::ostream &os )
{
    typename std::map<K, V>::const_iterator i = m.begin();
    while( i != m.end() )
    {
        fa( i->first, os );
        os << ms;
        fb( i->second, os );
        ++i;
        if( i != m.end() )
            os << is;
    }
}

#endif

