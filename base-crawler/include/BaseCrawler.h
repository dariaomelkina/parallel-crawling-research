#ifndef BASE_CRAWLER_BASECRAWLER_H
#define BASE_CRAWLER_BASECRAWLER_H

#include <vector>
#include "tbb/concurrent_queue.h"

/* TODO:
 *  constructors from file/db
 *  choose correct type of worker
 *  */

class BaseCrawler {
    /* Basic crawler, without html parsing, so it only establishes connections to urls from the queue,
     * without pushing any urls back to the queue. */
private:
    tbb::concurrent_queue<std::string> url_queue{};
    std::vector<std::string> visited_urls;
    // TODO: should we leave this parameters as int or as size_t?
    int urls_per_worker = 2;
    int number_of_workers = 1;
public:
    /* Basic constructor from a vector with urls. */
    BaseCrawler(const std::vector<std::string> &url_vector, int number_of_workers, int urls_per_worker);

    /* Basic run functions, wakes up workers. */
    void run();

    /* Pops urls from the queue and tries to connect to them. */
    void worker_version_1();

    /* TODO: I am not sure, which of these workers should be used,
     *  perhaps run() function should be different, too. */
    void worker_version_2();

    /* Establishes connection to server at the given url.
     * That function is going to depend on the chose method.
     * TODO: ????? or it will not*/
    bool send_request(const std::string &url);

    /* TODO: Or maybe that function will be different for each type of crawler? */
    void send_requests(const std::vector<std::string> &urls);
};


#endif //BASE_CRAWLER_BASECRAWLER_H
