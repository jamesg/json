#ifndef JSON_MAP_ACCESSOR_HPP
#define JSON_MAP_ACCESSOR_HPP

/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include "json.hpp"

/*
 * Namespace: json
 */
namespace json
{
    class map_accessor
    {
    public:
        map_accessor(const object& m)
        {
            const_cast<object&>(m) = cast<map>(const_cast<object&>(m));
            m_map = const_cast<map*>(&boost::get<map>(m));
        }

        map& get_object() const {
            return *m_map;
        }

        template<typename T>
        T& get(const std::string& k) const
        {
            return m_map->get<T>(k);
        }

        double& get_double(const std::string& s) const
        {
            return m_map->get_double(s);
        }
        int& get_int(const std::string& s) const
        {
            return m_map->get_int(s);
        }
        std::string& get_string(const std::string& s) const
        {
            return m_map->get_string(s);
        }
        list& get_list(const std::string& s) const
        {
            return m_map->get_list(s);
        }
        object& get_object(const std::string& s) const
        {
            return m_map->get_object(s);
        }
        map& get_map(const std::string& s) const
        {
            return m_map->get_map(s);
        }
        bool& get_bool(const std::string& s) const
        {
            return m_map->get_bool(s);
        }

        void operator=(const map_accessor& o) const
        {
            m_map->m_map = o.m_map->m_map;
        }

    private:
        mutable map *m_map;
    };

}

#endif

