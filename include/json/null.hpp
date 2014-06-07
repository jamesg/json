#ifndef JSON_NULL_HPP
#define JSON_NULL_HPP

/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

namespace json
{
    /*
     * Dummy type for the 'null' JSON value (boost::variant doesn't allow null
     * values otherwise).
     */
    class null_t {
    public:
        null_t()
        {
        }

        template <typename T, typename U>
        null_t(const T&, const U&)
        {
        }

        template <typename T>
        explicit null_t(const T&)
        {
        }
    };
}

#endif

