//
// Created by Maksym Protsyk on 5/13/21.
//

#include "ProcessSocketCrawler.h"
#include <bitset>


void ProcessSocketCrawler::parsing_process(size_t i) {

    // getting link from input queue
    std::string url = std::move(input_queue[i]);


    char* buffer = new char[MAX_SIZE];

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
    // closing connection
    close(sock);

    size_t tags = count_tags(buffer, index);

    sem_post(workers_sem_ptr);
    exit(0);
}

ProcessSocketCrawler::ProcessSocketCrawler(size_t max_workers): AbstractCrawler(max_workers) {

    // allocating shared memory
    workers_sem_ptr = (sem_t*) create_mmap(sizeof(sem_t));

    // shared semaphore
    sem_init(workers_sem_ptr, 1, max_workers);

}


void ProcessSocketCrawler::process_queue() {

    for (size_t i = 0; i < input_queue.size(); i++) {
        // wait till we can create a new worker
        sem_wait(workers_sem_ptr);
        // processing the url
        int id = fork();
        if (id == 0) {
            parsing_process(i);
        }


    }

    // waiting for all workers to finish
    for(size_t j = max_workers; j > 0; j--){
        sem_wait(workers_sem_ptr);
    }



}

ProcessSocketCrawler::~ProcessSocketCrawler() {
    sem_destroy(workers_sem_ptr);
    munmap(workers_sem_ptr, sizeof(sem_t));

}

void* ProcessSocketCrawler::create_mmap(size_t size) {
    // static method to created shared block of memory
    void* res = (void*) mmap(
            nullptr,
            size,
            PROT_READ | PROT_WRITE,
            MAP_SHARED | MAP_ANONYMOUS,
            -1,
            0
    );


    if (res == MAP_FAILED) {
        throw std::runtime_error("Can't allocate shared memory block");
    }

    return res;
}


