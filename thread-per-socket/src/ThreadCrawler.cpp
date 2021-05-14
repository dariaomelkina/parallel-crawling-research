//
// Created by Maksym Protsyk on 5/13/21.
//

#include "ThreadCrawler.h"


void *ThreadCrawler::parsing_thread(void *item) {
    auto args = (parsing_args_t *) item;

    //getting html using http request TODO: error handling
    auto html = send_request(args->url);


    // sending result to result queue
    pthread_mutex_lock(args->mutex_ptr);
    args->result_ptr->emplace(std::move(html));
    pthread_mutex_unlock(args->mutex_ptr);

    // increasing the number of available threads
    sem_post(args->sem_ptr);

    delete args;
    return nullptr;
}

void ThreadCrawler::process_url() {
    auto *args = new parsing_args_t;
    // getting url from the queue and passing args to the thread
    args->url = std::move(input_queue.front());
    input_queue.pop();
    args->sem_ptr = &sem;
    args->mutex_ptr = &mutex;
    args->result_ptr = &output_queue;

    pthread_t thread;
    pthread_create(&thread, nullptr, ThreadCrawler::parsing_thread, (void *) args);
    // detaching thread so that we don't need to store it later
    pthread_detach(thread);
    items_count += 1;
}

ThreadCrawler::ThreadCrawler(size_t max_workers) : AbstractCrawler(max_workers) {
    // mutex for output queue
    if (pthread_mutex_init(&mutex, nullptr) != 0) {
        throw std::runtime_error("Can't init the mutex");
    }
    // semaphore for the number of available workers
    if (sem_init(&sem, 0, max_workers) != 0) {
        throw std::runtime_error("Can't init the thread limit semaphore");
    }
}


void ThreadCrawler::process_queue() {

    while (!input_queue.empty()) {
        // wait till we can create a new worker
        sem_wait(&sem);
        // processing the url
        process_url();
    }

    // waiting for all workers to finish
    for (size_t i = 0; i < max_workers; i++) {
        sem_wait(&sem);
    }
}

ThreadCrawler::~ThreadCrawler() {
    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem);
}
