#ifndef PARSERS_QUOTED_STRING_DEF_HPP
#define PARSERS_QUOTED_STRING_DEF_HPP

/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include "quoted_string.hpp"

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>

using boost::spirit::qi::rule;
using boost::spirit::ascii::space_type;

template <typename Iterator>
struct parsers::quoted_string : boost::spirit::qi::grammar<Iterator,
	std::string(),
	boost::spirit::ascii::space_type>
{
    quoted_string();

	rule<Iterator, std::string(), space_type> qs;
	rule<Iterator, std::string(), space_type> start;
};

#endif


