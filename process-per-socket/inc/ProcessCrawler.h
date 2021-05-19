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

#define RESPONSE_BUFFER_SIZE 512

class ProcessCrawler: public AbstractCrawler {
protected:

    pthread_mutex_t* pipe_mut_ptr;
    int pipe_ends[2]{};

    virtual void parsing_process(size_t index);

public:
    explicit ProcessCrawler(size_t max_workers);

    virtual void process_queue();

    ~ProcessCrawler();

};



#endif //THREADS_PROCESSCRAWLER_H
