//
// Created by Maksym Protsyk on 5/5/21.
//

#ifndef CRAWLERS_REQUESTS_H
#define CRAWLERS_REQUESTS_H
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sstream>
#include <unistd.h>
#include <algorithm>
#include <exception>


#define RESPONSE_BUFFER_SIZE 512

const uint16_t HTTP_PORT = 80;


struct parsed_url_t {
    std::string domain;
    std::string path;
    std::string protocol;
};


parsed_url_t parse_url(const std::string& url);


std::string get_html(const std::string& url, const std::string& additional_params);

#endif //CRAWLERS_REQUESTS_H
