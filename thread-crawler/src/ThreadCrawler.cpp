//
// Created by Maksym Protsyk on 5/13/21.
//

#include "ThreadCrawler.h"
#include <iostream>


void *ThreadCrawler::parsing_thread(void *args) {
    auto params = (parsing_args_t *) args;
    pthread_barrier_wait(params->start_barrier_ptr);

    std::deque<std::string> *input_ptr = params->input_ptr;

    size_t size = input_ptr->size();

    char *buffer = new char[MAX_SIZE];


    for (size_t i = params->threads_index; i < size; i += params->threads_num) {
        int bytes_read = get_html(buffer, MAX_SIZE, (*input_ptr)[i], ADDITIONAL_PARAMS);
        if (bytes_read < 0) {
            continue;
        }
        size_t tags = count_tags(buffer, bytes_read);

    }

    delete[] params;
    delete[] buffer;

    return nullptr;

}


ThreadCrawler::ThreadCrawler(size_t max_workers) : AbstractCrawler(max_workers) {
    if (max_workers < 1) {
        throw std::runtime_error("There are no workers");
    }
    workers = new pthread_t[max_workers - 1];
}



void ThreadCrawler::start_workers() {

    pthread_barrier_init(&start_barrier, nullptr, max_workers);

    for (size_t i = 0; i < max_workers - 1; i++) {
        auto args = new parsing_args_t;
        args->input_ptr = &input_queue;
        args->threads_num = max_workers;
        args->threads_index = i;
        args->start_barrier_ptr = &start_barrier;
        pthread_create(&workers[i], nullptr, ThreadCrawler::parsing_thread, (void *) args);


    }

}


void ThreadCrawler::process_queue() {
    auto main_args = new parsing_args_t;
    main_args->input_ptr = &input_queue;
    main_args->threads_num = max_workers;
    main_args->threads_index = max_workers - 1;
    main_args->start_barrier_ptr = &start_barrier;

    ThreadCrawler::parsing_thread((void *) main_args);


    for (size_t i = 0; i < max_workers - 1; i++) {
        pthread_join(workers[i], nullptr);
    }

    input_queue.clear();
    pthread_barrier_destroy(&start_barrier);
}


ThreadCrawler::~ThreadCrawler() {
    delete[] workers;
}

