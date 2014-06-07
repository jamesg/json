/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include "json/parsers/json_number_def.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_lit.hpp>
#include <boost/spirit/include/qi_list.hpp>
#include <boost/spirit/include/qi_numeric.hpp>
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
using boost::phoenix::at_c;
using boost::phoenix::bind;
using boost::phoenix::push_back;
using boost::phoenix::ref;

template <typename Iterator>
parsers::json_number<Iterator>::json_number() :
    json_number::base_type( start )
{
    start = boost::spirit::qi::real_parser<>();
}

template parsers::json_number<std::string::const_iterator>::json_number();
template parsers::json_number<boost::spirit::istream_iterator>::json_number();

