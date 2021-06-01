#ifndef ASYNC_EPOLL_H
#define ASYNC_EPOLL_H

#include "pthread.h"
#include <unordered_map>
#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>
#include <csignal>


#include "AbstractCrawler.h"
#include "requests.h"

struct async_parsing_args_t {
    std::deque<std::string> *input_ptr;
    size_t threads_num;
    size_t threads_index;
    size_t max_requests;
    pthread_barrier_t* start_barrier_ptr;
};


enum sock_state{SOCK_IDLE, SOCK_CONNECTING, SOCK_READING, SOCK_WRITING};


struct html_getter_t {
    sock_state mode;
    char* buffer;
    size_t index;
    parsed_url_t parsed_url;
};

class EpollCrawler : public AbstractCrawler {
protected:
    size_t _max_requests;
    pthread_t* workers;
    pthread_barrier_t start_barrier{};

    static void *parsing_thread(void *args);

public:
    EpollCrawler(size_t max_workers, size_t max_requests);

    void process_queue() override;

    void start_workers() override;

    ~EpollCrawler();
};

#endif
