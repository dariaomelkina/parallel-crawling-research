//
// Created by Maksym Protsyk on 5/13/21.
//

#ifndef THREADS_TREADSOCKETCRAWLER_H
#define THREADS_TREADSOCKETCRAWLER_H

#include "semaphore.h"
#include "pthread.h"

#include "AbstractCrawler.h"


struct socket_parsing_args_t {
    std::string* url;
    sem_t *sem_ptr;
};


class ThreadSocketCrawler : public AbstractCrawler {
protected:
    sem_t sem{};

    static void *parsing_thread(void *item);


public:
    explicit ThreadSocketCrawler(size_t max_workers);

    virtual void process_queue();

    ~ThreadSocketCrawler();

};


#endif //THREADS_TREADSOCKETCRAWLER_H
