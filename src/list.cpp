/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include "json/json.hpp"

const json::object &json::list::at(int i)
{
    return objects.at(i);
}

json::object& json::list::operator[](int i)
{
    return objects[i];
}

json::list::size_type json::list::size() const
{
    return objects.size();
}

void json::list::append( const object& obj )
{
    objects.push_back(obj);
}

void json::list::append_list(const object& obj)
{
    const list& l = boost::get<list>(obj);
    for(auto o : l.objects)
        append(o);
}

void json::list::prepend(const object& o)
{
    objects.push_front(o);
}

void json::list::prepend_list(const object& o)
{
    const list& l = boost::get<list>(o);
    for(auto i = l.objects.crbegin(); i != l.objects.crend(); ++i)
        prepend(*i);
}

template<typename T>
T& json::list::get(size_type k) const
{
    objects[k] = json::cast<T>(objects[k]);
    return const_cast<T&>(boost::get<T>(objects.at(k)));
}

void json::list::clear()
{
    objects.clear();
}

template int& json::list::get<int>(json::list::size_type) const;
template double& json::list::get<double>(json::list::size_type) const;
template std::string& json::list::get<std::string>(json::list::size_type) const;
template json::list& json::list::get<json::list>(json::list::size_type) const;
template json::map& json::list::get<json::map>(json::list::size_type) const;

