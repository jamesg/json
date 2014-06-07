/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include "json/json.hpp"

#include <sstream>
#include <stdexcept>

#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <boost/spirit/include/qi.hpp>

#include "json/parsers/json_object_def.hpp"

#include "log.hpp"

using boost::spirit::ascii::space;

bool json::parse_json( const std::string &str, json::object &result )
{
    parsers::json_object<std::string::const_iterator> parser;
    std::string::const_iterator iter = str.begin();
    bool r = phrase_parse(
            iter, str.end(), parser, space, result );
    return r && iter == str.end();
}

std::string json::escape( std::string s )
{
    try
    {
        boost::regex e( std::string( "([\"])" ) );
        return boost::regex_replace( s, e, std::string( "\\\"" ) );
    }
    catch ( const std::exception &e )
    {
        json::log::debug( "json" ) << e.what() << std::endl;
    }
    return "";
}

std::string json::unescape( std::string s )
{
    boost::regex e( std::string( "\\\\(.)" ) );
    return boost::regex_replace( s, e, std::string( "$1" ) );
}

json::map::map(const object& o)
{
    map *m = boost::get<map>(&const_cast<object&>(o));
    if(m)
        m_map = m->m_map;
}

template<typename T> T& json::map::get( const std::string &k ) const
{
    T *t = boost::get<T>(&((*const_cast<json::map*>(this))[k]));
    if( t )
    {
        return *t;
    }
    else
    {
        std::map<std::string, json::object>::const_iterator it = m_map.find(k);
        if( it != m_map.end() )
        {
            // Attempt a cast
            try
            {
                json::object replacement = json::cast<T>(
                        const_cast<json::object&>(it->second)
                        );
                const_cast<json::map*>(this)->m_map[k] = replacement;
                return boost::get<T&>(const_cast<json::map*>(this)->m_map[k]);
            }
            catch( const std::exception& e )
            {
            }
        }
        const_cast<json::map*>(this)->m_map[k] = get_default<T>();
        return boost::get<T&>(const_cast<json::map*>(this)->m_map[k]);
    }
}

template double& json::map::get<double>(const std::string&) const;
template int& json::map::get<int>(const std::string&) const;
template std::string& json::map::get<std::string>(const std::string&) const;
template json::list& json::map::get<json::list>(const std::string&) const;
template json::map& json::map::get<json::map>(const std::string&) const;
template bool& json::map::get<bool>(const std::string&) const;

namespace json
{
    template<>
        json::object& map::get<json::object>( const std::string &k ) const
        {
            return const_cast<json::map*>(this)->m_map[k];
        }
}

template<> int json::get_default<int>() { return 0; }
template<> double json::get_default<double>() { return 0.0; }
template<> bool json::get_default<bool>() { return false; }

