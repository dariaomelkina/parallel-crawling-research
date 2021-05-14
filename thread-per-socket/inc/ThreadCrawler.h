//
// Created by Maksym Protsyk on 5/13/21.
//

#ifndef THREADS_THREADCRAWLER_H
#define THREADS_THREADCRAWLER_H

#include "AbstractCrawler.h"
#include "semaphore.h"
#include "pthread.h"

struct parsing_args_t {
    std::string url;
    std::queue<std::string>* result_ptr;
    pthread_mutex_t* mutex_ptr;
    sem_t* sem_ptr;
    sem_t* finish_sem_ptr;
};



class ThreadCrawler: public AbstractCrawler {
protected:
    sem_t sem{};
    sem_t finish_sem{};
    pthread_mutex_t mutex{};
    size_t items_count = 0;

    static void* parsing_thread(void* item);

    virtual void process_url();

public:
    explicit ThreadCrawler(size_t max_workers);

    virtual void process_queue();

    ~ThreadCrawler();

};



#endif //THREADS_THREADCRAWLER_H
