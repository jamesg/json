/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include <sstream>

#include "json/serialisers/vector.hpp"

std::string json::implode_string( const std::vector<std::string>& v,
        std::string sep )
{
    std::ostringstream oss;
    serialise(
            v,
            []( const std::string &s, std::ostream &os )
            {
                os << s;
            },
            sep,
            oss );
    return oss.str();
}

