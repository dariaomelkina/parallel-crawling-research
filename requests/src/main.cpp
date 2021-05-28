#include <iostream>
#include "requests.h"

/* For testing and demonstration purposes. */
int main() {

    std::string url = "http://google.com/";
    std::string additional_params = "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.97 Safari/537.36\r\n";

    char buffer[5000];
    std::cout << get_html(buffer, 5000, url, additional_params) << std::endl;
    std::cout << buffer << std::endl;
    return 0;
}

