#include <iostream>
#include <queue>
#include <string>
#include "EpollCrawler.h"


int main() {
    std::vector<std::string> test_urls = {"http://www.example.com/",
                                          "http://www.example.com/",
                                          "http://www.example.com/",
                                          "http://www.example.com/",
                                          "http://www.exmple.com/",
                                          "http://www.exmple.com/"};


    EpollCrawler x = EpollCrawler(3, 40);

    // adding links to the crawler
    for (size_t i = 0; i < 100; i++) {
        //std::cout << url << std::endl;
        x.add_url("http://www.example.com/");
        x.add_url("http://www.exmple.com/");
    }




    // processing links
    x.start_workers();
    x.process_queue();

    //sleep(100);

    return 0;
}
