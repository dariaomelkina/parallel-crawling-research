//
// Created by Maksym Protsyk on 5/13/21.
//

#ifndef THREADS_THREADCRAWLER_H
#define THREADS_THREADCRAWLER_H

#include "semaphore.h"
#include "pthread.h"

#include "AbstractCrawler.h"

struct parsing_args_t {
    std::deque <std::string>* input_ptr;
    size_t threads_num;
    size_t threads_index;
};

#define MAX_SIZE 500000
#define ONE_READ_SIZE 1000


class ThreadCrawler : public AbstractCrawler {
protected:

    static void* parsing_thread(void *args);

public:
    explicit ThreadCrawler(size_t max_workers);

    virtual void process_queue();


};


#endif //THREADS_THREADCRAWLER_H
