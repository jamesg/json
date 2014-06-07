#ifndef PARSERS_JSON_OBJECT_DEF_HPP
#define PARSERS_JSON_OBJECT_DEF_HPP

/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include "json_object.hpp"

#include <string>
#include <utility>
#include <vector>

#include <boost/scoped_ptr.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_real.hpp>
#include <boost/spirit/include/phoenix_core.hpp>

#include "../json.hpp"
#include "json_number_def.hpp"
#include "quoted_string_def.hpp"

using boost::spirit::qi::rule;
using boost::spirit::ascii::space_type;

template <typename Iterator>
struct parsers::json_object : boost::spirit::qi::grammar<Iterator,
	json::object(),
	boost::spirit::ascii::space_type>
{
    json_object();

    boost::scoped_ptr<quoted_string<Iterator>> string;
    boost::scoped_ptr<json_number<Iterator>> number;

    rule<Iterator, std::pair<std::string, json::object>(), space_type>
        json_pair;
    rule<Iterator, std::string(), space_type> json_string;

    rule<Iterator, std::vector<
            std::pair<std::string, json::object>
            >(),
        space_type
        > pair_list;
    rule<Iterator, json::map(), space_type> json_map;

    rule<Iterator, json::null_t(), space_type> json_null;

    rule<Iterator, json::list(), space_type> json_list;

    rule<Iterator, json::object(), space_type> object;

	rule<Iterator, json::object(), space_type> start;


};

#endif

