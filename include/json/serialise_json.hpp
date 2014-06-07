#ifndef JSON_SERIALISE_JSON_HPP
#define JSON_SERIALISE_JSON_HPP

/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include <string>

#include "json/object.hpp"

namespace json
{
    std::string serialise_json(const object&);
}

#endif

