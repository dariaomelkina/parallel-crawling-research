//
// Created by Maksym Protsyk on 5/13/21.
//

#include "ThreadCrawler.h"
#include <iostream>


void* ThreadCrawler::parsing_thread(void* args) {

    auto params = (parsing_args_t*) args;
    std::deque<std::string> *input_ptr = params->input_ptr;

    size_t size = input_ptr->size();


    for (size_t i = params->threads_index; i < size; i += params->threads_num) {
        std::string url = std::move((*input_ptr)[i]);

        int sock = get_socket(url);

        char buffer[MAX_SIZE];
        size_t index = 0;
        while (index < MAX_SIZE) {
            size_t char_read = read(sock, buffer + index, ONE_READ_SIZE);
            index += char_read;
            if (char_read == 0) {
                break;
            }
        }

        close(sock);



        size_t tags =  count_tags(buffer, index);


    }

    delete[] params;

    return nullptr;

}


ThreadCrawler::ThreadCrawler(size_t max_workers) : AbstractCrawler(max_workers) {}


void ThreadCrawler::process_queue() {

    auto threads = new pthread_t[max_workers];


    for (size_t i = 0; i < max_workers; i++) {
        auto args = new parsing_args_t;
        args->input_ptr = &input_queue;
        args->threads_num = max_workers;
        args->threads_index = i;
        pthread_create(&threads[i], nullptr, ThreadCrawler::parsing_thread, (void*) args);
    }


    for (size_t i = 0; i < max_workers; i++) {
        pthread_join(threads[i], nullptr);
    }

    input_queue.clear();

}

