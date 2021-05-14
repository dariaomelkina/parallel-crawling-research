cmake_minimum_required(VERSION 3.15.3)
project(threads)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads)
include_directories(inc ../abstract-crawler/inc ../requests/inc)

add_executable(threads src/main.cpp ../requests/inc/requests.h ../requests/src/requests.cpp
        ../abstract-crawler/inc/AbstractCrawler.h inc/ThreadCrawler.h
        ../abstract-crawler/src/AbstractCrawler.cpp src/ThreadCrawler.cpp)

target_link_libraries(threads ${CMAKE_THREAD_LIBS_INIT})