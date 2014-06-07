/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include "json/parsers/quoted_string_def.hpp"

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
using boost::spirit::qi::omit;
using boost::spirit::ascii::char_;
using boost::spirit::ascii::space;
using boost::spirit::ascii::space_type;
using boost::phoenix::at_c;
using boost::phoenix::bind;
using boost::phoenix::push_back;
using boost::phoenix::ref;

template <typename Iterator>
parsers::quoted_string<Iterator>::quoted_string() :
    quoted_string::base_type( start )
{
    qs = '"'  >> lexeme[+(char_ -  '"')[_val += _1]] >>  '"' |
         '\'' >> lexeme[+(char_ - '\'')[_val += _1]] >> '\'' |
         omit["\"\""] |
         omit["''"];
    start = ( qs[boost::phoenix::bind( &json::unescape, _1 )] )[_val = _1];
}

template parsers::quoted_string<std::string::const_iterator>::quoted_string();
template parsers::quoted_string<boost::spirit::istream_iterator>::quoted_string();

