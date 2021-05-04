// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

/* Demonstration of the most basic base crawler. */

#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
/* Trying out an http library (?) for c++
 * (a c++ wrapper for libcurl) */
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>

int main(int argc, char **argv) {
    std::queue<std::string> test_url_queue;
    test_url_queue.push("https://en.wikipedia.org/wiki/Greek_language");
//    test_queue.push("https://en.wikipedia.org/wiki/Cartography");

    curlpp::Cleanup myCleanup;
    std::ostringstream os;
    os << curlpp::options::Url(std::string("https://en.wikipedia.org/wiki/Greek_language"));

    std::cout << os.str() << std::endl;

    return 0;
}
