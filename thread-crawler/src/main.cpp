#include <iostream>
#include <queue>
#include <string>
#include "ThreadCrawler.h"


int main() {
    std::vector<std::string> test_urls = {"http://www.example.com/",
                                          "http://www.exmple.com/",
                                          "http://www.exmple.com/"};


    ThreadCrawler x = ThreadCrawler(1);

    // adding links to the crawler
    for (auto &url: test_urls) {
        //std::cout << url << std::endl;
        x.add_url(url);
    }

    // processing links
    x.process_queue();

    return 0;
}
