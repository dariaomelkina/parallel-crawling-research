# Parallel crawling research
Repository with implementation of crawlers from the corresponding paper.

## Description:
This repository holds implementations of three types of crawlers:
 * thread-per-socket
 * process-per-socket
 * using epoll
 
All three crawlers are based on the implementation of the abstract crawler.

There are also implementations of benchmarking, helper modules (such as directory parsing and
results visualization) and instructions for server setup.

## Global parameters:
In order for testing of the crawlers to be consistent and representative we have 
set some parameters, which should be the same for all the crawlers:
* **OS (for benchmarking):** Ubuntu 20.04 LTS
* **Compiler:** GCC 9.3.0 version
* **CMake:** 3.16+ version

## Credits:
* Oleg Farenyuk
* Vyacheslav Shevchuk
* Andriy Sultanov
* Maksym Protsyk
* Maksym Kuzyshyn
* Daria Omelkina

## License:
