#include <iostream>
#include <queue>
#include <string>
#include "EpollCrawler.h"


int main() {
    std::string test_url = "http://www.example.com/";

    EpollCrawler x = EpollCrawler(4, 100);
    x.add_from_file("../filtered_urls.txt", 400);


    // processing links
    x.process_queue();

    return 0;
}
