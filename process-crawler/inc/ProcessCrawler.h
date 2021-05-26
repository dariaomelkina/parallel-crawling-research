//
// Created by Maksym Protsyk on 5/13/21.
//

#ifndef THREADS_PROCESSCRAWLER_H
#define THREADS_PROCESSCRAWLER_H

#include "AbstractCrawler.h"
#include <unistd.h>
#include <pthread.h>
#include <cstring>
#include <cerrno>
#include <sys/mman.h>
#include <fcntl.h>
#include <string>
#include <iostream>
#include<sys/wait.h>


class ProcessCrawler : public AbstractCrawler {
protected:

    virtual void parsing_process(size_t index, pthread_barrier_t* start_barrier_ptr);

public:
    explicit ProcessCrawler(size_t max_workers);

    void process_queue() override;


};


#endif //THREADS_PROCESSCRAWLER_H
