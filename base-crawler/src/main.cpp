// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

/* Demonstration of the most basic base crawler. */

#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include "tbb/concurrent_queue.h"
#include <BaseCrawler.h>

/* For testing and demonstration purposes. */
int main(int argc, char **argv) {
    std::vector<std::string> test_urls = {"https://en.wikipedia.org/wiki/Green_anarchism",
                                          "https://en.wikipedia.org/wiki/IUCN_Red_List",
                                          "https://en.wikipedia.org/wiki/BirdLife_International",
                                          "https://en.wikipedia.org/wiki/Greek_language",
                                          "https://en.wikipedia.org/wiki/Cartography",
                                          "https://en.wikipedia.org/wiki/Gecko"};

    BaseCrawler crawler = BaseCrawler(test_urls, 2, 2);

    crawler.run();

    return 0;
}
