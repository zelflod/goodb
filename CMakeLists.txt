cmake_minimum_required(VERSION 3.13)
project(goodb)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Classes)

add_executable(test test.cpp)