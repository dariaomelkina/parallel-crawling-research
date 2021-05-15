cmake_minimum_required(VERSION 3.16)
project(google-benchmark CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(google-benchmark main.cpp)

find_package(benchmark REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(google-benchmark benchmark::benchmark Threads::Threads)


