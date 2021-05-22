//
// Created by Maksym Protsyk on 5/13/21.
//

#ifndef THREADS_ABSTRACTCRAWLER_H
#define THREADS_ABSTRACTCRAWLER_H

#include <queue>
#include <exception>
#include <utility>
#include <string>
#include <fstream>

#include "requests.h"


#define MAX_SIZE 500000
#define ONE_READ_SIZE 1000

/* Template for a crawler */
class AbstractCrawler {
protected:
    std::deque<std::string> input_queue;
    std::deque<std::string> output_queue;
    size_t max_workers;

public:
    explicit AbstractCrawler(size_t _max_workers) : max_workers(_max_workers) {};

    const static std::string ADDITIONAL_PARAMS;

    static int get_socket(const std::string &url);

    void add_url(const std::string &url);

    bool is_empty();

    std::string get_processed_item();

    virtual void process_queue() = 0;

    static size_t count_tags(const char* html, size_t html_size);

    void add_from_file(const std::string& filename);


};


#endif //THREADS_ABSTRACTCRAWLER_H
