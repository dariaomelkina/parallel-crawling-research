cmake_minimum_required(VERSION 3.19)
project(google-benchmark CXX)

set(CMAKE_CXX_STANDARD 14)

find_package(benchmark REQUIRED)

ADD_LIBRARY(LibsModule main.cpp)

target_link_libraries(LibsModule benchmark::benchmark)

add_executable(google-benchmark main.cpp)

target_link_libraries(google-benchmark LibsModule)

