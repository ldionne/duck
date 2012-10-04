cmake_minimum_required(VERSION 2.6)

project(duck)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11 -stdlib=libc++")
include_directories(include)
include_directories(${duck_SOURCE_DIR}/ext/mpl11/include)

add_subdirectory(test)
