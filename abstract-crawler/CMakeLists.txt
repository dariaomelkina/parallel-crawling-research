cmake_minimum_required(VERSION 3.15)
project(abstract-crawler)
set(CMAKE_CXX_STANDARD 20)

include_directories(inc)
add_executable(abstract-crawler src/AbstractCrawler.cpp inc/AbstractCrawler.h)
