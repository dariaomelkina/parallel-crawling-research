//
// Created by Maksym Protsyk on 5/13/21.
//

#ifndef THREADS_PROCESSSOCKETCRAWLER_H
#define THREADS_PROCESSSOCKETCRAWLER_H

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


class ProcessSocketCrawler : public AbstractCrawler {
protected:
    static void *create_mmap(size_t size);

    sem_t *workers_sem_ptr;

    virtual void parsing_process(size_t index);

public:
    explicit ProcessSocketCrawler(size_t max_workers);

    virtual void process_queue();

    ~ProcessSocketCrawler();

};


#endif //THREADS_PROCESSCRAWLER_H
