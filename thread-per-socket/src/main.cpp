#include <iostream>
#include <queue>
#include <string>
#include "TreadSocketCrawler.h"


int main() {
    std::vector<std::string> test_urls = {"http://www.example.com/",
                                          "http://www.exmple.com/",
                                          "http://www.exmple.com/"};


    TreadSocketCrawler x = TreadSocketCrawler(4);

    // adding links to the crawler
    for (auto &url: test_urls) {
        //std::cout << url << std::endl;
        x.add_url(url);
    }

    // processing links
    x.process_queue();

    // getting the output
    while (!x.is_empty()) {
        std::cout << x.get_processed_item() << std::endl;
    }

    return 0;
}
