cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAFS} -std=c++14")

project(custom_string)

add_subdirectory(custom_string_lib)
add_subdirectory(main)
