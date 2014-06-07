#ifndef JSON_MAP_HPP
#define JSON_MAP_HPP

/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include <map>
#include <string>

#include "json/json.hpp"

namespace json
{
    /*
     * A JSON map (normally known as a JSON object).  Represented using a C++
     * map.
     */
    struct map
    {
        map() {}
        map(const object& o);

        object& operator[](const std::string &k) const
        {
            return const_cast<json::map*>(this)->m_map[k];
        }

        // Variant accessor functions - may throw a boost::bad_get exception.

        // Generic 'get' function.
        template<typename T> T& get(const std::string &k) const;

        double &get_double(const std::string &k)  const
        {
            return get<double>(k);
        }
        int &get_int(const std::string &k) const
        {
            return get<int>(k);
        }
        list &get_list(const std::string &k) const
        {
            return get<list>(k);
        }
        std::string &get_string(const std::string &k) const
        {
            return get<std::string>(k);
        }
        map &get_map(const std::string &k) const
        {
            return get<map>(k);
        }
        object &get_object(const std::string &k) const
        {
            return const_cast<json::map*>(this)->m_map[k];
        }
        bool &get_bool(const std::string& k) const
        {
            return get<bool>(k);
        }

        void insert(const std::pair<std::string, json::object> &p)
        {
            m_map.insert(p);
        }

        friend std::string serialise_json(const object&);

        std::map<std::string, object> m_map;
    };
}

#endif

