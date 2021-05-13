cmake_minimum_required(VERSION 3.19)
project(google-benchmark CXX)

set(CMAKE_CXX_STANDARD 14)
# set (CMAKE_CXX_FLAGS "--benchmark_format=json")
# add_compile_options(--benchmark_format=json)

find_package(benchmark REQUIRED)

ADD_LIBRARY(LibsModule main.cpp)

target_link_libraries(LibsModule benchmark::benchmark)

add_executable(google-benchmark main.cpp)
# target_compile_options(google-benchmark PRIVATE --benchmark_format=json)

target_link_libraries(google-benchmark LibsModule)
