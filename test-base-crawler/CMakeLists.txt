cmake_minimum_required(VERSION 3.17)
project(base_crawler)

set(CMAKE_CXX_STANDARD 20)
#SET(CMAKE_CXX_COMPILER /usr/bin/g++)

include_directories(inc)
add_executable(test-base-crawler src/main.cpp src/BaseCrawler.cpp inc/BaseCrawler.h)

find_package(TBB REQUIRED COMPONENTS tbb)
find_package(Threads REQUIRED)
target_link_libraries(test-base-crawler TBB::tbb Threads::Threads)


# PVS-Studio: uncomment code below for testing
#if(UNIX AND NOT APPLE AND NOT CYGWIN)
#    inc(../cmake/PVS-Studio.cmake)
#    pvs_studio_add_target(TARGET lab4.analyze ALL
#            OUTPUT FORMAT errorfile
#            ANALYZE main
#            MODE GA:1,2 OP
#            LOG client.err)
#endif()