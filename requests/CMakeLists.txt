cmake_minimum_required(VERSION 3.15)
project(requests)

set(CMAKE_CXX_STANDARD 17)

include_directories(inc)
add_executable(requests src/main.cpp inc/requests.h src/requests.cpp)