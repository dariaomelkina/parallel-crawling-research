cmake_minimum_required(VERSION 3.17)
project(parallel-crawling-research)

set(CMAKE_CXX_STANDARD 20)
# TODO: we should use a specific version of gcc for benchmarking
#SET(CMAKE_CXX_COMPILER /usr/bin/g++)

include_directories(requests/inc thread-per-socket/inc abstract-crawler/inc)

add_executable(main-test
        # Main file (currently from thread-per-socket crawler directory) TODO: change
        thread-per-socket/src/main.cpp
        # Requests functions
        requests/inc/requests.h requests/src/requests.cpp
        # Thread-per-socket crawler
        thread-per-socket/inc/ThreadCrawler.h thread-per-socket/src/ThreadCrawler.cpp
        # Abstract crawler
        abstract-crawler/inc/AbstractCrawler.h abstract-crawler/src/AbstractCrawler.cpp)

find_package(Threads REQUIRED)
target_link_libraries(main-test Threads::Threads)

# TODO: sanitizers
# PVS-Studio: uncomment code below for testing
#if(UNIX AND NOT APPLE AND NOT CYGWIN)
#    inc(cmake/PVS-Studio.cmake)
#    pvs_studio_add_target(TARGET lab4.analyze ALL
#            OUTPUT FORMAT errorfile
#            ANALYZE main-test
#            MODE GA:1,2 OP
#            LOG client.err)
#endif()