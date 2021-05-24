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
_DRAFT_

In order for testing of the crawlers to be consistent and representative we have 
set some parameters, which should be the same for all the crawlers:
* **OS (for benchmarking):** Ubuntu (_which one?_)
* **Compiler:** gcc 10.2.0-6 version (_perhaps, we are not sure yet_)
* **CMake:** 3.16/3.17+ version

## Credits:
* Oleg Farenyuk
* Vyacheslav Shevchuk
* Andriy Sultanov
* Maksym Protsyk
* Maksym Kuzyshyn
* Daria Omelkina

## License:
