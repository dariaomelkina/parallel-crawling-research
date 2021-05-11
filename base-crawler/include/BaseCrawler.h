#ifndef BASE_CRAWLER_BASECRAWLER_H
#define BASE_CRAWLER_BASECRAWLER_H

#include <vector>
#include "tbb/concurrent_queue.h"

class BaseCrawler {
    /* Basic crawler, without html parsing, so it only establishes connections to urls from the queue,
     * without pushing any urls back to the queue. */
private:
    tbb::concurrent_queue<std::string> url_queue;
    std::vector<std::string> visited_urls;
    // TODO: should we leave this parameters as int or as size_t?
    int urls_per_worker = 2;
    int number_of_workers = 1;
public:
    BaseCrawler(tbb::concurrent_queue<std::string> &url_queue, int number_of_workers, int urls_per_worker);

    BaseCrawler(const std::vector<std::string> &url_vector, int number_of_workers, int urls_per_worker);

    void run();

    void crawl(const std::string& url);
};


#endif //BASE_CRAWLER_BASECRAWLER_H
