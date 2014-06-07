#ifndef JSON_CONVERT_HPP
#define JSON_CONVERT_HPP

/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include "json/object.hpp"

namespace json
{
    bool convert(object& from, object& to);
}

#endif

