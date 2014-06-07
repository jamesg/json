#ifndef PARSERS_JSON_NUMBER_DEF_HPP
#define PARSERS_JSON_NUMBER_DEF_HPP

/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include "json_number.hpp"

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>

using boost::spirit::qi::rule;
using boost::spirit::ascii::space_type;

template <typename Iterator>
struct parsers::json_number : boost::spirit::qi::grammar<Iterator,
    double,
	boost::spirit::ascii::space_type>
{
    json_number();

	rule<Iterator, double, space_type> start;
};

#endif


