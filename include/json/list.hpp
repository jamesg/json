#ifndef JSON_LIST_HPP
#define JSON_LIST_HPP

/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include <deque>

#include "json/cast.hpp"
#include "json/object.hpp"

namespace json
{
    // Simple JSON list type based on std::deque.  Represents a polymorphic
    // list.
    class list
    {
    public:
        typedef std::deque<object>::size_type size_type;

        mutable std::deque<object> objects;

        const object& at(int i);
        object& operator[](int i);
        size_type size() const;
        // Append a single object to the list.
        void append(const object& obj);
        // Apend all items in another JSON list to the end of this list.
        void append_list(const object& obj);
        void prepend(const object& o);
        void prepend_list(const object& o);
        template<typename T>
        T& get(size_type k) const;
        void clear();
    };
}

#endif

