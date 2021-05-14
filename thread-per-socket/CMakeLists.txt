cmake_minimum_required(VERSION 3.15.3)
project(threads)

set(CMAKE_CXX_STANDARD 17)
find_package (Threads)
include_directories(inc)

add_executable(threads src/main.cpp inc/requests.h src/requests.cpp inc/AbstractCrawler.h inc/ThreadCrawler.h src/AbstractCrawler.cpp src/ThreadCrawler.cpp)

target_link_libraries(threads ${CMAKE_THREAD_LIBS_INIT})