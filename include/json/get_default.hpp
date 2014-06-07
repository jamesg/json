#ifndef JSON_GET_DEFAULT_HPP
#define JSON_GET_DEFAULT_HPP

/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

namespace json
{
    // Get the default value for a JSON type.
    template <typename T> T get_default() { return T(); }
    template<> int get_default<int>();
    template<> double get_default<double>();
    template<> bool get_default<bool>();
}

#endif

