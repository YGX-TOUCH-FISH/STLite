cmake_minimum_required(VERSION 3.10.2)
project(STLite_ACM_main)

set(CMAKE_CXX_STANDARD 14)

include_directories(map)
include_directories(map/data)

add_executable(STLite_ACM_main
        map/data/seven.memcheck/code.cpp
        map/data/class-bint.hpp
        map/data/class-integer.hpp
        map/data/class-matrix.hpp
        map/exceptions.hpp
        map/utility.hpp
        map/map.hpp)
