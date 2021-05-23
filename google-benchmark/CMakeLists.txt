cmake_minimum_required(VERSION 3.15)
project(google-benchmark CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories(../thread-per-socket/inc ../abstract-crawler/inc ../requests/inc ../process-per-socket/inc ../async-epoll/inc)
add_executable(google-benchmark src/main.cpp ../thread-per-socket/src/ThreadCrawler.cpp
	../abstract-crawler/src/AbstractCrawler.cpp ../requests/src/requests.cpp ../process-per-socket/src/ProcessCrawler.cpp ../async-epoll/src/EpollCrawler.cpp)

find_package(benchmark REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(google-benchmark benchmark::benchmark Threads::Threads)


