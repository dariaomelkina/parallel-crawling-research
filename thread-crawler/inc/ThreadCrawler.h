//
// Created by Maksym Protsyk on 5/13/21.
//

#ifndef THREADS_THREADCRAWLER_H
#define THREADS_THREADCRAWLER_H

#include "semaphore.h"
#include "pthread.h"

#include "AbstractCrawler.h"

struct parsing_args_t {
    std::deque<std::string> *input_ptr;
    size_t threads_num;
    size_t threads_index;
    pthread_barrier_t* start_barrier_ptr;
};


class ThreadCrawler : public AbstractCrawler {
protected:

    pthread_t* workers;

    pthread_barrier_t start_barrier{};

    static void *parsing_thread(void *args);

public:
    explicit ThreadCrawler(size_t max_workers);

    void process_queue() override;

    void start_workers() override;

    ~ThreadCrawler();

};


#endif //THREADS_THREADCRAWLER_H
