//
// Created by Maksym Protsyk on 5/13/21.
//

#include "ThreadCrawler.h"
#include <iostream>


void* ThreadCrawler::parsing_thread(void* args) {

    auto params = (parsing_args_t*) args;
    std::deque<std::string> *input_ptr = params->input_ptr;

    size_t size = input_ptr->size();

    char* buffer = new char[MAX_SIZE];


    for (size_t i = params->threads_index; i < size; i += params->threads_num) {
        std::string url = std::move((*input_ptr)[i]);

        int sock = get_socket(url);

        size_t index = 0;
        while (index < MAX_SIZE - ONE_READ_SIZE) {
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
    delete[] buffer;

    return nullptr;

}


ThreadCrawler::ThreadCrawler(size_t max_workers) : AbstractCrawler(max_workers) {}


void ThreadCrawler::process_queue() {
    if (max_workers < 1) {
        throw std::runtime_error("There are no workers");
    }

    auto threads = new pthread_t[max_workers - 1];


    for (size_t i = 0; i < max_workers - 1; i++) {
        auto args = new parsing_args_t;
        args->input_ptr = &input_queue;
        args->threads_num = max_workers;
        args->threads_index = i;
        pthread_create(&threads[i], nullptr, ThreadCrawler::parsing_thread, (void*) args);
    }

    auto main_args = new parsing_args_t;
    main_args->input_ptr = &input_queue;
    main_args->threads_num = max_workers;
    main_args->threads_index = max_workers - 1;

    ThreadCrawler::parsing_thread((void*) main_args);


    for (size_t i = 0; i < max_workers - 1; i++) {
        pthread_join(threads[i], nullptr);
    }

    input_queue.clear();

    delete[] threads;


}

