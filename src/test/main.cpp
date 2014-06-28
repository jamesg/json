/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include <iostream>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "json/json.hpp"
#include "json/map_accessor.hpp"

SCENARIO("Basic parser tests", "[parser]") {
    GIVEN("A basic object") {
        const std::string basic_object = "{ \"a\": \"b\" }";
        json::object o;
        WHEN("The object is parsed") {
            bool status = json::parse_json(basic_object, o);
            THEN("We can access attribute a") {
                REQUIRE(status);
                REQUIRE(json::map_accessor(o).get_string("a") == "b");
            }
        }
    }
    GIVEN("An empty object") {
        const std::string empty_object = "{ }";
        json::object o;
        WHEN("The object is parsed") {
            bool status = json::parse_json(empty_object, o);
            THEN("The object was parsed successfully but is empty") {
                REQUIRE(status);
                REQUIRE(json::map_accessor(o).get_object().m_map.size() == 0);
            }
        }
    }
    GIVEN("A basic list") {
        const std::string basic_list = "[ \"a\", \"b\" ]";
        json::object o;
        WHEN("The list is parsed") {
            bool status = json::parse_json(basic_list, o);
            THEN("The list was parsed successfully") {
                REQUIRE(status);
            }
            THEN("The list contains members \"a\" and \"b\"") {
                REQUIRE(boost::get<json::list>(o).size() == 2);
                REQUIRE(boost::get<json::list>(o).get<std::string>(0) == "a");
                REQUIRE(boost::get<json::list>(o).get<std::string>(1) == "b");
            }
        }
    }
    GIVEN("An empty list") {
        const std::string empty_list = "[ ]";
        json::object o;
        WHEN("The list is parsed") {
            bool status = json::parse_json(empty_list, o);
            THEN("The list was parsed successfully") {
                REQUIRE(status);
            }
            THEN("The list is empty") {
                REQUIRE(boost::get<json::list>(o).size() == 0);
            }
        }
    }
}

SCENARIO("Advanced parser tests", "[parser]") {
    /*
     * The parser should be able to remove leading and training whitespace from
     * the objects it parses.
     */

    GIVEN("An empty list with whitespace") {
        const std::string empty_list = "  [ \n ]  \n ";
        json::object o;
        WHEN("The list is parsed") {
            bool status = json::parse_json(empty_list, o);
            THEN("The list was parsed successfully") {
                REQUIRE(status);
            }
            THEN("The list is empty") {
                REQUIRE(boost::get<json::list>(o).size() == 0);
            }
        }
    }
    GIVEN("An empty list with no whitespace") {
        const std::string empty_list = "[]";
        json::object o;
        WHEN("The list is parsed") {
            bool status = json::parse_json(empty_list, o);
            THEN("The list was parsed successfully") {
                REQUIRE(status);
            }
            THEN("The list is empty") {
                REQUIRE(boost::get<json::list>(o).size() == 0);
            }
        }
    }
}

