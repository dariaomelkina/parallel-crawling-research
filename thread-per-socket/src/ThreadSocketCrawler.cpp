//
// Created by Maksym Protsyk on 5/13/21.
//

#include "ThreadSocketCrawler.h"


void* ThreadSocketCrawler::parsing_thread(void *item) {
    auto args = (socket_parsing_args_t *) item;

    //getting html using http request TODO: error handling

    int sock = get_socket(*(args->url));

    char* buffer = new char[MAX_SIZE];

    size_t index = 0;
    while (index < MAX_SIZE) {
        size_t char_read = read(sock, buffer + index, MAX_SIZE);
        index += char_read;
        if (char_read == 0) {
            break;
        }
    }

    close(sock);

    size_t tags = count_tags(buffer, index);

    sem_post(args->sem_ptr);

    delete args;
    delete[] buffer;
    return nullptr;
}


ThreadSocketCrawler::ThreadSocketCrawler(size_t max_workers) : AbstractCrawler(max_workers) {
    // semaphore for the number of available workers
    if (sem_init(&sem, 0, 0) != 0) {
        throw std::runtime_error("Can't init the thread limit semaphore");
    }
}
#include <iostream>

void ThreadSocketCrawler::process_queue() {
    for (size_t i = 0; i < max_workers; i++) {
        sem_post(&sem);
    }

    for (size_t i = 0; i < input_queue.size(); i++) {
        // wait till we can create a new worker
        sem_wait(&sem);

        // processing the url
        auto args = new socket_parsing_args_t;
        args->sem_ptr = &sem;
        args->url = &input_queue[i];
        pthread_t thread;
        pthread_create(&thread, nullptr, ThreadSocketCrawler::parsing_thread, (void*) args);
    }

    // waiting for all workers to finish
    for (size_t i = 0; i < max_workers; i++) {
        sem_wait(&sem);
    }

    input_queue.clear();
}

ThreadSocketCrawler::~ThreadSocketCrawler() {
    sem_destroy(&sem);
}
