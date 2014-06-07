/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include "json/parsers/json_object_def.hpp"

#define BOOST_USE_PHOENIX_V3

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_lit.hpp>
#include <boost/spirit/include/qi_list.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

#include "json/json.hpp"

using namespace boost::spirit::qi::labels;
using boost::spirit::qi::lexeme;
using boost::spirit::qi::lit;
using boost::spirit::qi::rule;
using boost::spirit::qi::string;
using boost::spirit::ascii::char_;
using boost::spirit::ascii::space;
using boost::spirit::ascii::space_type;
using boost::spirit::omit;
using boost::phoenix::at_c;
using boost::phoenix::bind;
using boost::phoenix::push_back;
using boost::phoenix::ref;

BOOST_FUSION_ADAPT_STRUCT(
        json::list,
        (decltype(json::list::objects), objects)
)

namespace qi = boost::spirit::qi;

namespace
{
    std::pair<std::string, json::object> make_json_pair(
            std::string s,
            json::object o
            )
    {
        return std::make_pair(s, o);
    }
}

template <typename Iterator>
parsers::json_object<Iterator>::json_object() :
    json_object::base_type( start ),
    string ( new quoted_string<Iterator>() ),
    number ( new json_number<Iterator>() )
{
    json_pair = ( json_string >> ':' >> object )[
        qi::_val = boost::phoenix::bind(
                &make_json_pair,
                qi::_1,
                qi::_2
                )
        ];

    json_string = *string;
    pair_list = ( json_pair % ',' );

    json_map = ( '{' >> 
                 ( json_pair[boost::phoenix::bind(&json::map::insert,
                                                  _val,
                                                  _1
                                                  )
                             ] % ','
                   ) >>
                   '}'
                   ) |
               omit[char_('{') >> char_('}')];

    json_null = (omit[ "null" ])[_val = json::null_t()];

    json_list = '[' >>
                object[boost::phoenix::bind(&json::list::append,
                                            _val,
                                            _1
                                            )
                       ] % ',' >>
                ']' |
                omit[ char_('[') >> char_(']') ];

    object = json_string | json_map | json_list | json_null | boost::spirit::qi::int_ | boost::spirit::qi::double_;

    start = object.alias();
}

template parsers::json_object<std::string::const_iterator>::json_object();
template parsers::json_object<boost::spirit::istream_iterator>::json_object();

