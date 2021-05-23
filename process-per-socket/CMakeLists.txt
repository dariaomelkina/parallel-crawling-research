cmake_minimum_required(VERSION 3.15.3)
project(process_crawler)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads)

include_directories(inc ../abstract-crawler/inc ../requests/inc)

add_executable(process_crawler src/main.cpp ../requests/inc/requests.h ../requests/src/requests.cpp
        ../abstract-crawler/inc/AbstractCrawler.h inc/ProcessSocketCrawler.h
        ../abstract-crawler/src/AbstractCrawler.cpp src/ProcessSocketCrawler.cpp)

target_link_libraries(process_crawler ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(process_crawler ${Boost_LIBRARIES} rt)