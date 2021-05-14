cmake_minimum_required(VERSION 3.17)
project(base_crawler)

set(CMAKE_CXX_STANDARD 20)
# TODO: we should use a specific version of gcc for benchmarking
#SET(CMAKE_CXX_COMPILER /usr/bin/g++)

include_directories(test-base-crawler/include)
add_executable(main-test test-base-crawler/src/main.cpp test-base-crawler/src/BaseCrawler.cpp test-base-crawler/include/BaseCrawler.h)

find_package(TBB REQUIRED COMPONENTS tbb)
find_package(Threads REQUIRED)
target_link_libraries(main-test TBB::tbb Threads::Threads)


# TODO: PVS-studio, sanitizers
# PVS-Studio
#if(UNIX AND NOT APPLE AND NOT CYGWIN)
#    include(cmake/PVS-Studio.cmake)
#    pvs_studio_add_target(TARGET lab4.analyze ALL
#            OUTPUT FORMAT errorfile
#            ANALYZE main
#            MODE GA:1,2 OP
#            LOG client.err)
#endif()