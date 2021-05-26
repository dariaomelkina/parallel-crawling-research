#include "ProcessSocketCrawler.h"
#include <string>
#include <vector>


int main() {
    std::vector<std::string> test_urls = {"http://www.example.com/", "http://www.exmple.com/", "http://www.exmple.com/",
                                          "http://www.example.com/", "http://www.example.com/"};

    //size_t x = 0b11111100011111100101010101010111;
    //  for (size_t i = 0; i < sizeof(size_t); i++) {
    //      auto y = (char) (x >> 8 * i);
    //      std::cout << std::bitset<8>(y) << std::endl;
    // }


    ProcessSocketCrawler x = ProcessSocketCrawler(2);

    for (auto &url: test_urls) {
        std::cout << url << std::endl;
        x.add_url(url);
    }

    std::cout << "test" << std::endl;

    x.process_queue();


    while (!x.is_empty()) {
        std::cout << x.get_processed_item() << std::endl;
    }
}