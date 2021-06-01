#include "ProcessCrawler.h"
#include <string>
#include <vector>


int main() {
    std::vector<std::string> test_urls = {"http://www.example.com/",
                                          "http://www.example.com/",
                                          "http://www.example.com/",
                                          "http://www.example.com/",
                                          "http://www.exmple.com/",
                                          "http://www.exmple.com/"};


    ProcessCrawler x = ProcessCrawler(3);

    // adding links to the crawler
    for (auto &url: test_urls) {
        //std::cout << url << std::endl;
        x.add_url(url);
    }

    // processing links
    x.start_workers();

    x.process_queue();

}