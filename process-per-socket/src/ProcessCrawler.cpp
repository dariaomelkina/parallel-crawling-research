//
// Created by Maksym Protsyk on 5/13/21.
//

#include "ProcessCrawler.h"




void ProcessCrawler::process_url() {
    std::string url = std::move(input_queue.front());
    input_queue.pop();
    int pid = fork();
    if (pid == 0) {

        std::string html = send_request(url);
        char  digits[sizeof(size_t)];
        for (size_t i = 0; i < sizeof(size_t); i++) {
            digits[i] = (char) (html.length() >> (8 * i));
        }

        pthread_mutex_lock(pipe_mut_ptr);
        write(pipe_ends[1], digits, sizeof(size_t));

        write(pipe_ends[1], html.c_str(), html.length());
        close(pipe_ends[1]);
        pthread_mutex_unlock(pipe_mut_ptr);
        sem_post(workers_sem_ptr);
        exit(0);
    }
}

ProcessCrawler::ProcessCrawler(size_t max_workers): AbstractCrawler(max_workers) {
    workers_sem_name = "/sem" + std::to_string(id);
    pipe_mut_name = "/mut" + std::to_string(id);
    shm_unlink(pipe_mut_name.c_str());
    shm_unlink(workers_sem_name.c_str());
    id += 1;
    int pipe_mutex_descriptor = shm_open(pipe_mut_name.c_str(), O_CREAT | O_RDWR | O_TRUNC, S_IRWXU | S_IRWXG);

    if (pipe_mutex_descriptor < 0) {
        throw std::runtime_error("Can't create mutex descriptor");
    }

    if (ftruncate(pipe_mutex_descriptor, sizeof(pthread_mutex_t)) == -1) {
        throw std::runtime_error("Can't ftruncate to the size of mutex");
    }


    pipe_mut_ptr = (pthread_mutex_t*) mmap(
        nullptr,
        sizeof(pthread_mutex_t),
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        pipe_mutex_descriptor,
        0
    );


    if (pipe_mut_ptr == MAP_FAILED) {
        throw std::runtime_error("Can't allocate shared memory block");
    }

    pthread_mutexattr_t pipe_mutex_attr;
    pthread_mutexattr_setpshared(&pipe_mutex_attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(pipe_mut_ptr, &pipe_mutex_attr);



    int sem_descriptor = shm_open(workers_sem_name.c_str(), O_CREAT | O_RDWR | O_TRUNC, S_IRWXU | S_IRWXG);

    if (sem_descriptor < 0) {
        throw std::runtime_error("Can't create semaphore descriptor");
    }

    if (ftruncate(sem_descriptor, sizeof(sem_t)) == -1) {
        throw std::runtime_error("Can't ftruncate to the size of semaphore");
    }


    workers_sem_ptr = (sem_t*) mmap(
        NULL,
        sizeof(sem_t),
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        sem_descriptor,
        0
    );


    if (workers_sem_ptr == MAP_FAILED) {
        throw std::runtime_error("Can't allocate shared memory block");
    }

    // shared semaphore
    sem_init(workers_sem_ptr, 1, max_workers);

    pipe(pipe_ends);
}


void ProcessCrawler::process_queue() {
    size_t processes = 0;

    while (!input_queue.empty()) {
        // wait till we can create a new worker
        sem_wait(workers_sem_ptr);
        // processing the url
        process_url();
        processes += 1;
    }

    // waiting for all workers to finish
    for(size_t j = processes; j > 0; j--){
        wait(nullptr);
    }


    for (size_t i = 0; i < processes; i++) {
        char digits[sizeof(size_t)];

        // getting number of bytes to read
        if (read(pipe_ends[0], digits, sizeof(size_t)) != sizeof(size_t)) {
            throw std::runtime_error("Can't read number of bytes from buffer");
        }
        size_t num = 0;
        for (size_t j = 0; j < sizeof(size_t); j++) {
            num += (size_t) digits[j] << (8 * j);
        }

        char *html = new char[num];

        if (read(pipe_ends[0], html, num) != num) {
            throw std::runtime_error("Can't read html");
        }

        output_queue.emplace(html);
        delete[] html;

    }

}

ProcessCrawler::~ProcessCrawler() {
    pthread_mutex_destroy(pipe_mut_ptr);
    sem_destroy(workers_sem_ptr);
    shm_unlink(pipe_mut_name.c_str());
    shm_unlink(workers_sem_name.c_str());

}



size_t ProcessCrawler::id = 0;
