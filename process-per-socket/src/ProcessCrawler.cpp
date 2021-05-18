//
// Created by Maksym Protsyk on 5/13/21.
//

#include "ProcessCrawler.h"
#include <bitset>


void ProcessCrawler::process_url() {

    // getting link from input queue
    std::string url = std::move(input_queue.front());
    input_queue.pop();

    // allocating block of memory shared between processes
    char* shared_html = (char*) create_mmap(MAX_SIZE);

    int pid = fork();

    // main process returns here
    if (pid != 0) {
        return;
    }

    // getting socket descriptor
    int sock = get_socket(url);

    // reading data to buffer
    // TODO: remove the buffer and read directly into shared memory
    char buffer[MAX_SIZE];
    size_t len = read(sock, buffer, MAX_SIZE);

    // closing connection
    close(sock);

    // copying data to shared memory (!!will be changed)
    memcpy(shared_html, buffer, len);

    // closing one end of pipe
    close(pipe_ends[0]);


    pthread_mutex_lock(pipe_mut_ptr);
    // sending pointer to the shared data to the main process
    write(pipe_ends[1], &shared_html, sizeof(char*));
    pthread_mutex_unlock(pipe_mut_ptr);

    close(pipe_ends[1]);


    pthread_mutex_lock(items_mut_ptr);
    // adding one available item
    *available_items += 1;
    pthread_mutex_unlock(items_mut_ptr);

    // notifying the main process that this worker has finished
    sem_post(workers_sem_ptr);
    exit(0);
}

ProcessCrawler::ProcessCrawler(size_t max_workers): AbstractCrawler(max_workers) {

    // allocating shared memory
    pipe_mut_ptr = (pthread_mutex_t*) create_mmap(sizeof(pthread_mutex_t));
    items_mut_ptr = (pthread_mutex_t*) create_mmap(sizeof(pthread_mutex_t));
    workers_sem_ptr = (sem_t*) create_mmap(sizeof(sem_t));

    // shared mutexes
    pthread_mutexattr_t mutex_attr;
    pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(pipe_mut_ptr, &mutex_attr);
    pthread_mutex_init(items_mut_ptr, &mutex_attr);


    // shared semaphore
    sem_init(workers_sem_ptr, 1, max_workers);

    // initializing pipe
    pipe(pipe_ends);

    // creating shared memory block to store the number of available items
    available_items = (int*) create_mmap(sizeof(int));
    *available_items = 0;
}


void ProcessCrawler::process_queue() {

    while (!input_queue.empty()) {
        // wait till we can create a new worker
        sem_wait(workers_sem_ptr);
        // processing the url
        process_url();

        // getting the output if it is available
        move_to_queue();

    }

    // waiting for all workers to finish
    for(size_t j = max_workers; j > 0; j--){
        sem_wait(workers_sem_ptr);
        move_to_queue();
    }

    close(pipe_ends[1]);

}

ProcessCrawler::~ProcessCrawler() {
    pthread_mutex_destroy(pipe_mut_ptr);
    pthread_mutex_destroy(items_mut_ptr);
    sem_destroy(workers_sem_ptr);
    munmap(available_items, sizeof(int));

}

void* ProcessCrawler::create_mmap(size_t size) {
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

void ProcessCrawler::move_to_queue() {
    // checks if item is available
    bool available = false;
    pthread_mutex_lock(items_mut_ptr);
    if (*available_items > 0) {
        *available_items -= 1;
        available = true;
    }
    pthread_mutex_unlock(items_mut_ptr);

    // returns if there are no available items
    if (!available) {
        return;
    }

    // reading pointer to shared data
    char* item_ptr;
    read(pipe_ends[0], &item_ptr, sizeof(char*));

    // sending item to the output
    output_queue.emplace(item_ptr);

    // freeing allocated memory
    munmap(item_ptr, MAX_SIZE);

}


