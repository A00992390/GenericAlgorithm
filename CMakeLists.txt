cmake_minimum_required(VERSION 3.15)
project(GenericAlgorithm)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
add_executable(GenericAlgorithm main.cpp City.cpp City.hpp Tour.cpp Tour.hpp genetic_op.cpp genetic_op.hpp)