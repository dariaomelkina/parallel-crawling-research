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
#include <stack>

#include "requests.h"


#define MAX_SIZE 4000000

/* Template for a crawler */
class AbstractCrawler {
protected:
    std::deque<std::string> input_queue;
    size_t max_workers;

public:
    explicit AbstractCrawler(size_t _max_workers) : max_workers(_max_workers) {};

    const static std::string ADDITIONAL_PARAMS;

    void add_url(const std::string &url);

    bool is_empty();

    virtual void process_queue() = 0;

    virtual void start_workers() = 0;

    static size_t count_tags(const char *html, size_t html_size);

    void add_from_file(const std::string &filename, int64_t num_websites);
};


#endif //THREADS_ABSTRACTCRAWLER_H
