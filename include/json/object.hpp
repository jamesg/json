#ifndef JSON_OBJECT_HPP
#define JSON_OBJECT_HPP

/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include <boost/variant.hpp>

#include "json/null.hpp"

namespace json
{
    class list;
    class map;

    typedef boost::recursive_wrapper<std::string> r_string;
    typedef boost::recursive_wrapper<map> r_map;
    typedef boost::recursive_wrapper<list> r_list;

    typedef boost::variant<null_t, r_map, std::string, r_list, double, int, bool>
        object;
}

#endif

