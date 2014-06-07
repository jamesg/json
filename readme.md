JSON Library
============

This is a JSON library for C++ which features lenient type checking.  It can be
used like typical JSON libraries, where members of objects are accessed using a
'member("json_key")' type syntax.  Alternatively, it can be used where JSON
structures almost replace C++ structs, providing access to a fixed set of named
member.

## Data Types

The JSON library defines data types analogous to JSON objects, lists and null
types.  Other 'atomic' types are provided by bool, double, int and std::string.
The json::object type is a boost::variant of all the other types.

## Implementation

The library is implemented in C++ and uses the Boost Spirit and Boost Variant
libraries.

## Building

The parsers and serialisers can be built by running 'make libjson.a' in the
source directory.  libjson.a should be added to the compiler line for your own
program to link against the JSON library.

Include the library headers when compiling your own programs by adding
-Ijson/include (where json is the location of the JSON library).

## Usage

Most library types and functions are included by #include "json/json.hpp".  The
map accessor type and generic serialisers (used internally but made part of the
library) must be included seperately: #include "json/map_accessor.hpp".

### Parse a String

    #include "json/json.hpp"
    ...
    // An object to store the result.
    json::object o;

    json::parse_json("{ \"a\": \"b\" }", o);

### Serialise a String

Very similar to parsing.

    #include "json/json.hpp"
    ...
    // o is a json::object
    std::string s;
    json::serialise_json(o, s);

### Accessing Members

    #include "json/map_accessor.hpp"
    ...
    json::map_accessor accessor(o);
    std::string a = accessor.get_string("a");

This step is quite error prone.  What if the structure of the JSON object is
changed (say, the 'a' field is removed)?  Other code using the structure may
not be updated as a result of the change and would no longer work as expected.

### Typed Structures

Typed structures prevent objects from being used incorrectly by accident.

    #include "json/map_accessor.hpp"
    ...
    struct photograph : json::map_accessor
    {
        photograph(json::object& o) :
            json::map_accessor(o)
        {
        }
        std::string& title() const { return get_string("title"); }
        int& album_id() const { return get_int("album_id"); }
    }

If the photograph structure is requested from an API and the album_id field is
removed, it only needs to be removed at one point in the code to prevent the
program compiling.

