#ifndef ASYNC_EPOLL_H
#define ASYNC_EPOLL_H

#include "pthread.h"
#include <unordered_map>
#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>


#include "AbstractCrawler.h"

struct async_parsing_args_t {
    std::deque<std::string> *input_ptr;
    size_t threads_num;
    size_t threads_index;
    size_t max_requests;
};

class EpollCrawler : public AbstractCrawler {
protected:
    size_t _max_requests;

    static void *parsing_thread(void *args);

public:
    EpollCrawler(size_t max_workers, size_t max_requests);

    virtual void process_queue();
};

#endif
