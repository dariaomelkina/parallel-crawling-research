#ifndef BASE_CRAWLER_BASECRAWLER_H
#define BASE_CRAWLER_BASECRAWLER_H

#include <vector>
#include "tbb/concurrent_queue.h"

class BaseCrawler {
private:
    tbb::concurrent_queue<std::string> url_queue;
    std::vector<std::string> visited_urls;
    int urls_per_worker = 2;
public:
    BaseCrawler(tbb::concurrent_queue<std::string> url_queue, int urls_per_worker = 2);

    BaseCrawler(std::vector<std::string> url_vector, int urls_per_worker = 2);

    void run();

    void crawl(std::string url);
};


#endif //BASE_CRAWLER_BASECRAWLER_H
