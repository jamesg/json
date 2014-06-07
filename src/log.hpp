#ifndef LOG_HPP
#define LOG_HPP

/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include <iostream>
#include <string>

/*
 * File: log.hpp
 */

/*
 * Namespace: json
 */
namespace json
{
    /*
     * Namespace: log
     *
     * Functions for obtaining output streams that can be used to log debugging
     * information.  Each function requires the name of the component providing
     * debugging output.  This name and the current configuration determine the end
     * location of the output.
     */
    namespace log {
        /*
         * Typedef: stream_t
         */
        typedef std::ostream& stream_t;
        /*
         * Function: debug
         */
        stream_t debug(std::string component);
        /*
         * Function: info
         */
        stream_t info(std::string component);
        /*
         * Function: warn
         */
        stream_t warn(std::string component);
        /*
         * Function: error
         */
        stream_t error(std::string component);
        /*
         * Function: output
         */
        stream_t output();
    }
}

#endif
