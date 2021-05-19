//
// Created by Maksym Protsyk on 5/13/21.
//

#include "ThreadCrawler.h"


void* ThreadCrawler::parsing_thread(void* args) {
    auto params = (parsing_args_t*) args;
    std::deque<std::string> *input_ptr = params->input_ptr;
    std::deque<std::string> *output_ptr = params->output_ptr;
    pthread_mutex_t *input_mutex_ptr = params->input_mutex_ptr;
    pthread_mutex_t *output_mutex_ptr = params->output_mutex_ptr;

    while (true) {
        pthread_mutex_lock(params->input_mutex_ptr);
        if (params->input_ptr->empty()) {
            pthread_mutex_unlock(input_mutex_ptr);
            break;
        }
        std::string url = std::move(input_ptr->front());
        input_ptr->pop_front();
        pthread_mutex_unlock(input_mutex_ptr);

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
}

<<<<<<< HEAD
=======
void ThreadCrawler::process_url() {
    auto *args = new parsing_args_t;
    // getting url from the queue and passing args to the thread
    args->url = std::move(input_queue.front());
    input_queue.pop_front();
    args->sem_ptr = &sem;
    args->mutex_ptr = &mutex;
    args->result_ptr = &output_queue;

    pthread_t thread;
    pthread_create(&thread, nullptr, ThreadCrawler::parsing_thread, (void *) args);
    // detaching thread so that we don't need to store it later
    pthread_detach(thread);
    items_count += 1;
}
>>>>>>> 353c1f11795f93eea6a80ec9215f3051a3bed0a4

ThreadCrawler::ThreadCrawler(size_t max_workers) : AbstractCrawler(max_workers) {
    // mutex for the input queue
    if (pthread_mutex_init(&input_mutex, nullptr) != 0) {
        throw std::runtime_error("Can't init the input mutex ");
    }

    // mutex for the output queue
    if (pthread_mutex_init(&output_mutex, nullptr) != 0) {
        throw std::runtime_error("Can't init the output mutex");
    }
}


void ThreadCrawler::process_queue() {
    parsing_args_t args{};
    args.input_mutex_ptr = &input_mutex;
    args.output_mutex_ptr = &output_mutex;
    args.input_ptr = &input_queue;
    args.output_ptr = &output_queue;
    void* args_ptr =  (void*) &args;

    auto threads = new pthread_t[max_workers];


    for (size_t i = 0; i < max_workers; i++) {
        pthread_create(&threads[i], nullptr, ThreadCrawler::parsing_thread, args_ptr);
    }


    for (size_t i = 0; i < max_workers; i++) {
        pthread_join(threads[i], nullptr);
    }


}

ThreadCrawler::~ThreadCrawler() {
    pthread_mutex_destroy(&input_mutex);
    pthread_mutex_destroy(&output_mutex);
}
