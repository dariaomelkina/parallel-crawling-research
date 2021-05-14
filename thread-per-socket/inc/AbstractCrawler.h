//
// Created by Maksym Protsyk on 5/13/21.
//

#ifndef THREADS_ABSTRACTCRAWLER_H
#define THREADS_ABSTRACTCRAWLER_H

#include <queue>
#include <requests.h>
#include <exception>
#include <utility>

/* template for a crawle */
class AbstractCrawler {
protected:
    std::queue<std::string> input_queue;
    std::queue<std::string> output_queue;
    size_t max_workers;

    virtual void process_url() = 0;

public:
    explicit AbstractCrawler(size_t _max_workers) : max_workers(_max_workers){};

    const static std::string ADDITIONAL_PARAMS;

    static std::string send_request(const std::string& url);

    void add_url(std::string& url);

    bool is_empty();

    std::string get_processed_item();

    virtual void process_queue() = 0;


};



#endif //THREADS_ABSTRACTCRAWLER_H
