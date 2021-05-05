cmake_minimum_required(VERSION 3.15)
project(crawlers)

set(CMAKE_CXX_STANDARD 17)

include_directories(inc)
add_executable(crawlers src/main.cpp inc/requests.h src/requests.cpp)