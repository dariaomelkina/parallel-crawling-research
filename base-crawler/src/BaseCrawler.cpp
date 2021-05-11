#include "BaseCrawler.h"

BaseCrawler::BaseCrawler(tbb::concurrent_queue<std::string> &url_queue, int number_of_workers = 1,
                         int urls_per_worker = 2) {
}

BaseCrawler::BaseCrawler(const std::vector<std::string> &url_vector, int number_of_workers, int urls_per_worker) {}

void BaseCrawler::run() {}

void BaseCrawler::crawl(const std::string &url) {}