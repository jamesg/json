cmake_minimum_required(VERSION 2.6)
project(JSON)

set(CMAKE_CXX_FLAGS "-std=c++0x")

include_directories(include)
file(GLOB sources src/*.cpp)
file(GLOB parsers_sources src/parsers/*.cpp)
file(GLOB serialisers_sources src/serialisers/*.cpp)

add_library(
    json
    ${sources}
    ${parsers_sources}
    ${serialisers_sources}
    )

