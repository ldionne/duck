cmake_minimum_required(VERSION 2.8)

project(duck)

add_definitions(-Wall -Wextra -pedantic -std=c++11)
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    add_definitions(-stdlib=libc++)
endif()

include_directories(include)

find_package(Boost 1.51 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(test)
