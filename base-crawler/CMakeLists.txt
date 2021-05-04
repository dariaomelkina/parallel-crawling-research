cmake_minimum_required(VERSION 3.17)
project(base_crawler)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_COMPILER /usr/bin/g++)


include_directories(include)
add_executable(main src/main.cpp)

# TODO: PVS-studio, sanitizers
# PVS-Studio
#if(UNIX AND NOT APPLE AND NOT CYGWIN)
#    # TODO: change to a correct path to PVS-studio, perhaps it will be same for the whole repository
#    include(cmake/extra/PVS-Studio.cmake)
#    pvs_studio_add_target(TARGET lab4.analyze ALL
#            OUTPUT FORMAT errorfile
#            ANALYZE main
#            MODE GA:1,2 OP
#            LOG client.err)
#endif()