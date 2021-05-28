//
// Created by Maksym Protsyk on 5/13/21.
//

#include "ProcessCrawler.h"
#include <iostream>


void ProcessCrawler::parsing_process(size_t index, pthread_barrier_t* start_barrier_ptr) {
    pthread_barrier_wait(start_barrier_ptr);

    char *buffer = new char[MAX_SIZE];

    for (size_t i = index; i < input_queue.size(); i += max_workers) {
        size_t bytes_read = get_html(buffer, MAX_SIZE, input_queue[i], ADDITIONAL_PARAMS);
        size_t tags = count_tags(buffer, bytes_read);
    }

    delete[] buffer;
}

ProcessCrawler::ProcessCrawler(size_t max_workers) : AbstractCrawler(max_workers) {}


void ProcessCrawler::process_queue() {
    if (max_workers == 0) {
        throw std::runtime_error("There are no workers");
    }

    // barrier that allows all processes to start their work at the same time
    auto *start_barrier_ptr = (pthread_barrier_t *) mmap(
            nullptr,
            sizeof(pthread_barrier_t),
            PROT_READ | PROT_WRITE,
            MAP_SHARED | MAP_ANONYMOUS,
            -1,
            0
    );

    pthread_barrierattr_t start_barrier_attr;
    pthread_barrierattr_init(&start_barrier_attr);
    pthread_barrierattr_setpshared(&start_barrier_attr, PTHREAD_PROCESS_SHARED);

    pthread_barrier_init(start_barrier_ptr, &start_barrier_attr, max_workers);

    pthread_barrierattr_destroy(&start_barrier_attr);


    for (size_t i = 0; i < max_workers - 1; i++) {
        int id = fork();
        if (id < 0) {
            throw std::runtime_error("Can't fork");
        } else if (id == 0) {
            parsing_process(i, start_barrier_ptr);
            exit(0);
        }

    }

    parsing_process(max_workers - 1, start_barrier_ptr);

    for (size_t i = 0; i < max_workers - 1; i++) {
        wait(nullptr);
    }

    input_queue.clear();
    pthread_barrier_destroy(start_barrier_ptr);
    munmap(start_barrier_ptr, sizeof(pthread_barrier_t));
}




