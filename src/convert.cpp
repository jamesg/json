/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include "json/convert.hpp"

#include <boost/lexical_cast.hpp>

#include "json/json.hpp"

namespace
{
    class convert_visitor : public boost::static_visitor<bool>
    {
        public:
        bool operator()(double & from, double & to) const
        {
            to = from;
            return true;
        }
        bool operator()(double & from, int & to) const
        {
            to = static_cast<int>(from);
            return true;
        }
        bool operator()(double & from, std::string & to) const
        {
            std::ostringstream oss;
            oss << from;
            to = oss.str();
            return true;
        }
        bool operator()(double &, json::map &) const
        {
            return false;
        }
        bool operator()(double &, json::list &) const
        {
            return false;
        }
        bool operator()(double & from, json::null_t & to) const
        {
            to = json::get_default<json::null_t>();
            return true;
        }
        bool operator()(double & from, bool & to) const
        {
            return false;
        }

        bool operator()(int & to, double & from) const
        {
            to = static_cast<int>(from);
            return true;
        } //< loss of precision
        bool operator()(int & from, int & to) const
        {
            to = from;
            return true;
        }
        bool operator()(int & from, std::string & to) const
        {
            std::ostringstream oss;
            oss << from;
            to = oss.str();
            return true;
        }
        bool operator()(int &, json::map &) const
        {
            return false;
        }
        bool operator()(int &, json::list &) const
        {
            return false;
        }
        bool operator()(int & from, json::null_t & to) const
        {
            to = json::get_default<json::null_t>();
            return true;
        }
        bool operator()(int & from, bool & to) const
        {
            to = (from > 0);
            return true;
        }

        bool operator()(std::string & from, int & to) const
        {
            to = boost::lexical_cast<int>(from);
            return true;
        }
        bool operator()(std::string & from, double & to) const
        {
            to = boost::lexical_cast<double>(from);
            return true;
        }
        bool operator()(std::string & from, std::string & to) const
        {
            to = from;
            return true;
        }
        bool operator()(std::string &, json::map &) const
        {
            return false;
        }
        bool operator()(std::string& from, json::list& to) const {
            if( from.length() == 0 ) {
                to = json::list();
                return true;
            } else {
                return false;
            }
        }
        bool operator()(std::string& from, json::null_t& to) const
        {
            to = json::get_default<json::null_t>();
            return true;
        }
        bool operator()(std::string& from, bool& to) const
        {
            return false;
        }

        bool operator()(json::map&, int&) const
        {
            return false;
        }
        // Converting from a map to a string is allowed only if the map is
        // empty.
        bool operator()(json::map& from, std::string& to) const
        {
            if( from.m_map.size() == 0 ) {
                to = "";
                return true;
            } else {
                return false;
            }
        }
        bool operator()(json::map&, double&) const
        {
            return false;
        }
        bool operator()(json::map& from, json::map & to) const
        {
            to = from;
            return true;
        }
        // Converting from a map to a list is allowed only if the map is empty.
        bool operator()(json::map& from, json::list& to) const
        {
            if( from.m_map.size() == 0 ) {
                to = json::list();
                return true;
            } else {
                return false;
            }
        }
        bool operator()(json::map & from, json::null_t & to) const
        {
            to = json::get_default<json::null_t>();
            return true;
        }
        bool operator()(json::map& from, bool& to) const
        {
            return false;
        }

        bool operator()(json::list &, int &) const
        {
            return false;
        }
        bool operator()(json::list &, std::string &) const
        {
            return false;
        }
        bool operator()(json::list& from, json::map &) const
        {
            return from.size() == 0;
        }
        bool operator()(json::list &, double &) const
        {
            return false;
        }
        bool operator()(json::list & from, json::list & to) const
        {
            to = from; return true;
        }
        bool operator()(json::list & from, json::null_t & to) const
        {
            to = json::get_default<json::null_t>();
            return true;
        }
        bool operator()(json::list& from, bool& to) const
        {
            return false;
        }

        bool operator()(json::null_t &, double & to) const
        {
            to = json::get_default<double>();
            return true;
        }
        bool operator()(json::null_t &, int & to) const
        {
            to = json::get_default<int>();
            return true;
        }
        bool operator()(json::null_t &, std::string & to) const
        {
            to = json::get_default<std::string>();
            return true;
        }
        bool operator()(json::null_t &, json::map & to) const
        {
            to = json::get_default<json::map>();
            return true;
        }
        bool operator()(json::null_t &, json::list & to) const
        {
            to = json::get_default<json::list>();
            return true;
        }
        bool operator()(json::null_t & from, json::null_t & to) const
        {
            to = from;
            return true;
        }
        bool operator()(json::null_t& from, bool& to) const
        {
            to = false;
            return true;
        }

        bool operator()(bool & from, double & to) const
        {
            return false;
        }
        bool operator()(bool & from, int & to) const
        {
            return false;
        }
        bool operator()(bool & from, std::string & to) const
        {
            return false;
        }
        bool operator()(bool & from, json::map & to) const
        {
            return false;
        }
        bool operator()(bool & from, json::list & to) const
        {
            return false;
        }
        bool operator()(bool & from, json::null_t & to) const
        {
            to = json::get_default<json::null_t>();
            return true;
        }
        bool operator()(bool & from, bool & to) const
        {
            to = from;
            return true;
        }
    };
}

bool json::convert(object& from, object& to)
{
    return boost::apply_visitor(convert_visitor(), from, to);
}

