cmake_minimum_required(VERSION 3.17)
project(parallel-crawling-research)

set(CMAKE_CXX_STANDARD 20)
# TODO: we should use a specific version of gcc for benchmarking
#SET(CMAKE_CXX_COMPILER /usr/bin/g++)

include_directories(requests/inc thread-per-socket/inc)
add_executable(main-test thread-per-socket/src/main.cpp requests/inc/requests.h requests/src/requests.cpp
        thread-per-socket/inc/ThreadCrawler.h thread-per-socket/src/ThreadCrawler.cpp
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