//
// Created by Maksym Protsyk on 5/13/21.
//

#ifndef THREADS_THREADCRAWLER_H
#define THREADS_THREADCRAWLER_H

#include "semaphore.h"
#include "pthread.h"

#include "AbstractCrawler.h"

#define RESOPONSE_BUFFER_SIZE 512

struct parsing_args_t {
    std::string url;
    std::queue <std::string> *result_ptr;
    pthread_mutex_t *mutex_ptr;
    sem_t *sem_ptr;
};


class ThreadCrawler : public AbstractCrawler {
protected:
    sem_t sem{};
    pthread_mutex_t mutex{};
    size_t items_count = 0;

    static void *parsing_thread(void *item);

    virtual void process_url();

public:
    explicit ThreadCrawler(size_t max_workers);

    virtual void process_queue();

    ~ThreadCrawler();

};


#endif //THREADS_THREADCRAWLER_H
