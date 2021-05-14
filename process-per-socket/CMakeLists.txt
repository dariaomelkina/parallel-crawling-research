cmake_minimum_required(VERSION 3.15.3)
project(process)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads)

include_directories(inc ../abstract-crawler/inc ../requests/inc)

add_executable(process src/main.cpp ../requests/inc/requests.h ../requests/src/requests.cpp
        ../abstract-crawler/inc/AbstractCrawler.h inc/ProcessCrawler.h
        ../abstract-crawler/src/AbstractCrawler.cpp src/ProcessCrawler.cpp)

target_link_libraries(process ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(threads ${Boost_LIBRARIES} rt)