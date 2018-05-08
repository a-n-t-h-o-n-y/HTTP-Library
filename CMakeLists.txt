cmake_minimum_required(VERSION 3.2)
enable_testing()
project(HTTP_Library)

# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

add_subdirectory(src)
add_subdirectory(test)

