cmake_minimum_required(VERSION 3.17)
project(directory-parser)

set(CMAKE_CXX_STANDARD 20)

include_directories(inc)

add_executable(parser src/main src/directory_parser.cpp inc/directory_parser.h)

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
