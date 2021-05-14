#include <thread>
#include <iostream>
#include "BaseCrawler.h"

BaseCrawler::BaseCrawler(const std::vector<std::string> &url_vector, int number_of_workers, int urls_per_worker) {
    /* TODO: maybe there is a better way to do it.*/
    /* Put urls into the queue. */
    for (const auto &url:url_vector) {
        this->url_queue.push(url);
    }

    /* Set other parameters. */
    this->number_of_workers = number_of_workers;
    this->urls_per_worker = urls_per_worker;
}

void BaseCrawler::run() {
    /* Create vector for workers. */
    std::vector<std::thread> workers;
    workers.reserve(this->number_of_workers);

    /* Wake up workers. */
    for (int i = 0; i < this->number_of_workers; i++) {
        workers.emplace_back(&BaseCrawler::worker_version_2, this);
    }

    /* Workers go back to eternal sleep. */
    for (auto &i: workers) {
        i.join();
    }
}

// The function for a synchronous worker, we can just change it to version_2 but provide 
// a limit for the queue
void BaseCrawler::worker_version_1() {
    while (!this->url_queue.empty()) {
        std::string url;
        bool successful_connection;

        /* Finish work, if the queue is completely empty. */
        if (!url_queue.try_pop(url)) {
            break;
        }

        /* Trying to establish a connection to the url. */
        successful_connection = send_request(url);
        if (successful_connection) {
            this->visited_urls.push_back(url);
        }
    }
}

// A function for an asynchronous worker
void BaseCrawler::worker_version_2() {
    while (!this->url_queue.empty()) {
        std::vector<std::string> urls_to_connect;
        urls_to_connect.reserve(this->urls_per_worker);

        /* Popping urls, which will be processed by that worker. */
        for (int i = 0; i < this->urls_per_worker; i++) {
            std::string url;
            if (!url_queue.try_pop(url)) {
                break;
            } else {
                urls_to_connect.push_back(url);
            }
        }

        /* Trying to establish connections to urls. */
        send_requests(urls_to_connect);

        /* TODO: we should somehow check, if connections were successful. */
    }
}

bool BaseCrawler::send_request(const std::string &url) {
    std::cout << "(?) Request method will be different for each crawler. (?)" << std::endl;
    std::cout << "Sending request to " << url << std::endl;
    return true;
}

void BaseCrawler::send_requests(const std::vector<std::string> &urls) {
    std::cout << "\n//////////////////////////////////////////////////////////" << std::endl;
    std::cout << "(?) Request method will be different for each crawler. (?)" << std::endl;
    for (const auto &i:urls) {
        std::cout << "Connecting to: " << i << std::endl;
    }
    std::cout << "//////////////////////////////////////////////////////////\n" << std::endl;
}
