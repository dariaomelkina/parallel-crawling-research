//
// Created by Maksym Protsyk on 5/13/21.
//

#ifndef THREADS_PROCESSCRAWLER_H
#define THREADS_PROCESSCRAWLER_H

#include "AbstractCrawler.h"
#include "semaphore.h"
#include "pthread.h"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <cstring>
#include <cerrno>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <string>
#include <iostream>
#include <semaphore.h>
#include<sys/wait.h>
#include <iostream>


class ProcessCrawler: public AbstractCrawler {
protected:
    std::string workers_sem_name;
    std::string pipe_mut_name;
    static size_t id;
    sem_t* workers_sem_ptr;
    pthread_mutex_t* pipe_mut_ptr;
    int pipe_ends[2]{};


    virtual void process_url();

public:
    explicit ProcessCrawler(size_t max_workers);

    virtual void process_queue();

    ~ProcessCrawler();

};



#endif //THREADS_PROCESSCRAWLER_H
