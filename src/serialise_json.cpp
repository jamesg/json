/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include "json/json.hpp"

#include <sstream>

#include "json/serialisers/deque.hpp"
#include "json/serialisers/map.hpp"
#include "json/serialisers/vector.hpp"
#include "json/serialisers/string.hpp"

std::string json::serialise_json(const object &jobj)
{
    class serialise_visitor : public boost::static_visitor<void>
    {
        public:
        serialise_visitor(std::ostream &os) :
            output_stream(os)
        {
        }

        void operator()(const std::string& str) const
        {
            output_stream << "\"";
            serialise(escape(str), output_stream);
            output_stream << "\"";
        }

        void operator()(const r_map& map) const
        {
            output_stream << "{ ";
            json::serialise(
                    map.get().m_map,
                    [](const std::string &s, std::ostream &os)
                    {
                        os << "\"" << escape(s) << "\"";
                    },
                    [](const json::object &o, std::ostream &os)
                    {
                        boost::apply_visitor(serialise_visitor(os), o);
                    },
                    " : ",
                    ", ",
                    output_stream
                    );
            output_stream << " }";
        }

        void operator()(const r_list& list) const
        {
            output_stream << "[ ";
            json::serialise(
                list.get().objects,
                [](const json::object &o, std::ostream &os) {
                    boost::apply_visitor(serialise_visitor(os), o);
                },
                ", ",
                output_stream
                );
            output_stream << " ]";
        }

        void operator()(const double& d) const
        {
            std::ostringstream oss;
            oss << d;
            output_stream << oss.str();
        }

        void operator()(const int& d) const
        {
            std::ostringstream oss;
            oss << d;
            output_stream << oss.str();
        }

        void operator()(const null_t&) const
        {
            output_stream << "null";
        }

        void operator()(const bool& b) const
        {
            output_stream << (b?"true":"false");
        }

        private:
        std::ostream &output_stream;
    };

    std::ostringstream oss;
    boost::apply_visitor(serialise_visitor(oss), jobj);

    return oss.str();
}

