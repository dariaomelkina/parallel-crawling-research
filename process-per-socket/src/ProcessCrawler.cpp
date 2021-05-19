//
// Created by Maksym Protsyk on 5/13/21.
//

#include "ProcessCrawler.h"


void ProcessCrawler::parsing_process(size_t index) {
    // closing reading end
    close(pipe_ends[0]);

    // getting link from input queue
    for (size_t i = index; i < input_queue.size(); i += max_workers) {
        std::string url = std::move(input_queue[i]);

        // getting socket descriptor
        int sock = get_socket(url);

        // reading data to buffer
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

        size_t len = response.size();


        pthread_mutex_lock(pipe_mut_ptr);
        write(pipe_ends[1], &len, 8);
        write(pipe_ends[1], &response[0], response.size());
        pthread_mutex_unlock(pipe_mut_ptr);

    }

    close(pipe_ends[1]);
}

ProcessCrawler::ProcessCrawler(size_t max_workers): AbstractCrawler(max_workers) {


    // allocating shared memory
    pipe_mut_ptr = (pthread_mutex_t*) mmap(
            nullptr,
            sizeof(pthread_mutex_t),
            PROT_READ | PROT_WRITE | PROT_EXEC,
            MAP_SHARED | MAP_ANONYMOUS,
            -1,
            0
    );

    if (pipe_mut_ptr == MAP_FAILED) {
        throw std::runtime_error("Can't allocate shared memory block");
    }

    // sharing the mutex
    pthread_mutexattr_t mutex_attr;
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(pipe_mut_ptr, &mutex_attr);
    pthread_mutexattr_destroy(&mutex_attr);


    // initializing pipe
    pipe(pipe_ends);

}


void ProcessCrawler::process_queue() {

    for (size_t i = 0; i < max_workers; i++) {
        int id = fork();
        if (id < 0) {
            throw std::runtime_error("Can't fork");
        }

        else if (id == 0) {
            parsing_process(i);
            exit(0);
        }

    }

    // closing writing end
    close(pipe_ends[1]);


    // waiting for all items
    for(size_t i = 0; i < input_queue.size(); i++){
        size_t html_size = 0;
        size_t chars_read;

        // getting the length of html file
        chars_read = read(pipe_ends[0], &html_size, sizeof(size_t));
        if (chars_read != sizeof(size_t)) {
            throw std::runtime_error("Can't read html size from pipe");
        }

        // allocating memory for html

        auto html_chars = new char[html_size];

        // reading html file from file
        chars_read = read(pipe_ends[0], html_chars, html_size);
        if (chars_read != html_size) {
            throw std::runtime_error("Can't read html from pipe");
        }
        output_queue.emplace_back(html_chars);
        delete[] html_chars;

    }

    // closing reading end
    close(pipe_ends[0]);

    for (size_t i = 0; i < max_workers; i++) {
        wait(nullptr);
    }

}

ProcessCrawler::~ProcessCrawler() {
    pthread_mutex_destroy(pipe_mut_ptr);
    munmap(pipe_mut_ptr, sizeof(pthread_mutex_t));

}




