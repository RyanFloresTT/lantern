cmake_minimum_required(VERSION 4.2)
project(lantern)

set(CMAKE_CXX_STANDARD 20)

add_library(lantern STATIC library.cpp)
target_include_directories(cmake_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
