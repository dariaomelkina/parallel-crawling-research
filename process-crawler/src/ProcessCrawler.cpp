//
// Created by Maksym Protsyk on 5/13/21.
//

#include "ProcessCrawler.h"
#include <iostream>


void ProcessCrawler::parsing_process(size_t index) {
    char* buffer = new char[MAX_SIZE];

    // getting link from input queue
    for (size_t i = index; i < input_queue.size(); i += max_workers) {
        std::string url = std::move(input_queue[i]);

        // getting socket descriptor
        int sock = get_socket(url);

        // reading data to buffer
        size_t index = 0;
        while (index < MAX_SIZE) {
            size_t char_read = read(sock, buffer + index, MAX_SIZE);
            index += char_read;
            if (char_read == 0) {
                break;
            }
        }
        close(sock);



        size_t tags =  count_tags(buffer, index);

    }

    delete[] buffer;

}

ProcessCrawler::ProcessCrawler(size_t max_workers): AbstractCrawler(max_workers) {}


void ProcessCrawler::process_queue() {
    if (max_workers == 0) {
        std::runtime_error("There are no workers");
    }

    for (size_t i = 0; i < max_workers - 1; i++) {
        int id = fork();
        if (id < 0) {
            throw std::runtime_error("Can't fork");
        }

        else if (id == 0) {
            parsing_process(i);
            exit(0);
        }

    }

    parsing_process(max_workers - 1);



    for (size_t i = 0; i < max_workers - 1; i++) {
        wait(nullptr);
    }

    input_queue.clear();

}




