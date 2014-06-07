/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include <iostream>

#include "log.hpp"

namespace
{
    class nullstream : public std::ostream
    {
        template <typename T>
        nullstream &operator << ( T ) { return *this; }
    };

    nullstream g_nullstream;
}

std::ostream& json::log::debug(std::string component) {
	std::cerr << "DEBUG " << component << " ";
	return std::cerr;
}

std::ostream& json::log::info(std::string component) {
	std::cerr << "INFO " << component << " ";
	return std::cerr;
}

std::ostream& json::log::warn(std::string component) {
	std::cerr << "WARN " << component << " ";
	return std::cerr;
}

std::ostream& json::log::error(std::string component) {
	std::cerr << "ERROR " << component << " ";
	return std::cerr;
}

std::ostream& json::log::output() {
	return std::cout;
}

