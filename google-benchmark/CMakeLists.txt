cmake_minimum_required(VERSION 3.15)
project(google-benchmark CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(../thread-crawler/inc ../abstract-crawler/inc ../requests/inc
        ../process-crawler/inc ../async-epoll/inc)
add_executable(google-benchmark src/main.cpp ../thread-crawler/src/ThreadCrawler.cpp
        ../abstract-crawler/src/AbstractCrawler.cpp ../requests/src/requests.cpp
        ../process-crawler/src/ProcessCrawler.cpp ../async-epoll/src/EpollCrawler.cpp)

find_package(benchmark REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(google-benchmark benchmark::benchmark Threads::Threads)


