// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

/* Demonstration of the most basic base crawler. */

#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include "tbb/concurrent_queue.h"


int main(int argc, char **argv) {
    tbb::concurrent_queue<std::string> test_url_queue;
    test_url_queue.push("https://en.wikipedia.org/wiki/Greek_language");
    test_url_queue.push("https://en.wikipedia.org/wiki/Cartography");
    test_url_queue.push("");
    test_url_queue.push("");
    test_url_queue.push("");


    return 0;
}
