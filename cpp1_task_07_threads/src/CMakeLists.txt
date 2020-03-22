cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAFS} -std=c++14")

project(paralel_merge_sort)

add_executable(paralel_merge_sort main.cpp)

