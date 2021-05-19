//
// Created by Maksym Protsyk on 5/13/21.
//

#ifndef THREADS_THREADCRAWLER_H
#define THREADS_THREADCRAWLER_H

#include "semaphore.h"
#include "pthread.h"

#include "AbstractCrawler.h"

#define RESPONSE_BUFFER_SIZE 512

struct parsing_args_t {
    std::deque <std::string>* output_ptr;
    std::deque <std::string>* input_ptr;
    pthread_mutex_t* output_mutex_ptr;
    size_t threads_num;
    size_t threads_index;
};


class ThreadCrawler : public AbstractCrawler {
protected:
    pthread_mutex_t output_mutex{};

    static void* parsing_thread(void *args);

public:
    explicit ThreadCrawler(size_t max_workers);

    virtual void process_queue();

    ~ThreadCrawler();

};


#endif //THREADS_THREADCRAWLER_H
