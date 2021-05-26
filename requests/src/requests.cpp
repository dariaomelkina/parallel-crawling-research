//
// Created by Maksym Protsyk on 5/5/21.
//
#include "requests.h"
#include <iostream>

parsed_url_t parse_url(const std::string &url) {
    parsed_url_t parsed_url;

    const std::string separator = "://";
    std::string::const_iterator protocol_itr = std::search(
            url.begin(), url.end(),
            separator.begin(), separator.end()
    );
    //if (protocol_itr == url.end()) {
        //throw std::runtime_error("Invalid url");
    //}
    size_t protocol_index = protocol_itr - url.begin();
    parsed_url.protocol = url.substr(0, protocol_index);

    size_t domain_index = url.find(
            '/', protocol_index + 3
    );

    parsed_url.domain = url.substr(protocol_index + 3, domain_index - protocol_index - 3);
    if (domain_index == std::string::npos) {
        parsed_url.path = "/";
    } else {
        parsed_url.path = url.substr(domain_index, std::string::npos);
    }


    return parsed_url;

}


int send_request(const std::string &url, const std::string &additional_params) {
    parsed_url_t parsed_url = parse_url(url);

    uint16_t port;
    if (parsed_url.protocol == "http") {
        port = HTTP_PORT;
    } else {
        throw std::runtime_error("Only http");
    }

    struct hostent *host;
    host = gethostbyname(parsed_url.domain.c_str());

    struct sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    // std::cout << *((unsigned long *) host->h_addr) << std::endl;
    server.sin_addr.s_addr = 2516593162;//*((unsigned long *) host->h_addr);

    // creating socket descriptor
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        throw std::runtime_error("Can't create socket");
    }

    // establishing a connection
    if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        throw std::runtime_error("Can't connect to host");
    }

    // building a http request that takes html from the given website
    std::stringstream req_stream;
    req_stream << "GET " << parsed_url.path << " HTTP/1.1\r\n"
               << "Host: " << parsed_url.domain << "\r\n"
               << additional_params
               << "Connection: close\r\n"
               << "\r\n";
    std::string request = req_stream.str();


    // sending http request
    if (send(sock, request.c_str(), request.size(), 0) < 0) {
        throw std::runtime_error("Error while sending request");
    }


    return sock;

}
