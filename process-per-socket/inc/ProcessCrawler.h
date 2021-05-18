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

#define PROCESS_BUFFER_SIZE 512
#define MAX_SIZE 10000

class ProcessCrawler: public AbstractCrawler {
protected:
    static void* create_mmap(size_t size);

    sem_t* workers_sem_ptr;
    pthread_mutex_t* pipe_mut_ptr;
    pthread_mutex_t* items_mut_ptr;
    int pipe_ends[2]{};
    int* available_items;

    void move_to_queue();
    virtual void process_url();

public:
    explicit ProcessCrawler(size_t max_workers);

    virtual void process_queue();

    ~ProcessCrawler();

};



#endif //THREADS_PROCESSCRAWLER_H
