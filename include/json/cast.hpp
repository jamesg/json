#ifndef JSON_CAST_HPP
#define JSON_CAST_HPP

/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include <sstream>
#include <stdexcept>

#include "json/get_default.hpp"
#include "json/object.hpp"
#include "json/serialise_json.hpp"

namespace json
{
    bool convert(json::object&, json::object&);
    // Cast a JSON value to a compatible type, or throw an exception if the
    // target type is incompatible.
    template<typename Tto> Tto cast(json::object& from)
    {
        json::object to = get_default<Tto>();
        if(!convert(from, to))
        {
            std::ostringstream oss;
            oss << "invalid json cast from " << serialise_json(from) <<
                " to " << serialise_json(to);
            throw std::runtime_error(oss.str());
        }

        return boost::get<Tto>(to);
    }
}

#endif

