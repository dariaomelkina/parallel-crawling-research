//
// Created by Maksym Protsyk on 5/13/21.
//

#include "ThreadCrawler.h"
#include <iostream>


void* ThreadCrawler::parsing_thread(void* args) {

    auto params = (parsing_args_t*) args;
    std::deque<std::string> *input_ptr = params->input_ptr;
    std::deque<std::string> *output_ptr = params->output_ptr;
    pthread_mutex_t *output_mutex_ptr = params->output_mutex_ptr;

    size_t size = input_ptr->size();


    for (size_t i = params->threads_index; i < size; i += params->threads_num) {
        std::string url = std::move((*input_ptr)[i]);

        int sock = get_socket(url);

        std::string response{};
        char buffer[RESPONSE_BUFFER_SIZE];
        while (true) {
            size_t char_read = read(sock, buffer, RESPONSE_BUFFER_SIZE);
            if (char_read == 0) {
                break;
            }
            response.append(buffer, char_read);
        }
        close(sock);


        pthread_mutex_lock(output_mutex_ptr);
        output_ptr->emplace_back(std::move(response));
        pthread_mutex_unlock(output_mutex_ptr);

    }

    delete[] params;

    return nullptr;

}


ThreadCrawler::ThreadCrawler(size_t max_workers) : AbstractCrawler(max_workers) {

    // mutex for the output queue
    if (pthread_mutex_init(&output_mutex, nullptr) != 0) {
        throw std::runtime_error("Can't init the output mutex");
    }
}


void ThreadCrawler::process_queue() {

    auto threads = new pthread_t[max_workers];


    for (size_t i = 0; i < max_workers; i++) {
        auto args = new parsing_args_t;
        args->output_mutex_ptr = &output_mutex;
        args->input_ptr = &input_queue;
        args->output_ptr = &output_queue;
        args->threads_num = max_workers;
        args->threads_index = i;
        pthread_create(&threads[i], nullptr, ThreadCrawler::parsing_thread, (void*) args);
    }


    for (size_t i = 0; i < max_workers; i++) {
        pthread_join(threads[i], nullptr);
    }

    input_queue.clear();

}

ThreadCrawler::~ThreadCrawler() {
    pthread_mutex_destroy(&output_mutex);
}
