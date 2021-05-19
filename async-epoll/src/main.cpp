#include <iostream>
#include <queue>
#include <string>
#include "EpollCrawler.h"


int main() {
  std::string test_url = "http://www.example.com/";


  EpollCrawler x = EpollCrawler(4);

  // adding links to the crawler
  for (size_t i = 0; i < 100; ++i) {
    x.add_url(test_url);
  }

  // processing links
  x.process_queue();

  // getting the output
  while (!x.is_empty()) {
    std::cout << x.get_processed_item() << std::endl;
  }

  return 0;
}