cmake_minimum_required(VERSION 3.16)
project(asyncepoll)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads)
include_directories(inc ../abstract-crawler/inc ../requests/inc)

add_executable(asyncepoll src/main.cpp ../requests/src/requests.cpp
        ../abstract-crawler/src/AbstractCrawler.cpp src/EpollCrawler.cpp)

target_link_libraries(asyncepoll ${CMAKE_THREAD_LIBS_INIT})