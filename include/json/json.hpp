#ifndef JSON_HPP
#define JSON_HPP

/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include <deque>
#include <map>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include "json/cast.hpp"
#include "json/get_default.hpp"
#include "json/list.hpp"
#include "json/map.hpp"
#include "json/null.hpp"
#include "json/object.hpp"
#include "json/serialisers/map.hpp"
#include "json/serialisers/vector.hpp"

/*
 * C++ JSON library with lenient typechecking.
 */
namespace json
{
    std::string escape(std::string);
    std::string unescape(std::string);
    bool parse_json(const std::string&, object&);
}

#endif

