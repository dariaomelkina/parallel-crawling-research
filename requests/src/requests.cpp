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



int connect_to_host(int sock, const parsed_url_t& parsed_url) {
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

    if (!host || !host->h_addr) {
        std::cout << "ERROR: host adress is null {" << parsed_url.domain << "}" << std::endl;
        return -1;
    }

    server.sin_addr.s_addr = *((unsigned long *) host->h_addr);

    return connect(sock, (struct sockaddr *) &server, sizeof(server));

}


int send_request(int sock, const parsed_url_t& parsed_url, const std::string& additional_params) {
    std::stringstream req_stream;
    req_stream << "GET " << parsed_url.path << " HTTP/1.1\r\n"
               << "Host: " << parsed_url.domain << "\r\n"
               << additional_params
               << "Connection: close\r\n"
               << "\r\n";
    std::string request = req_stream.str();


    // sending http request
    size_t res = send(sock, request.c_str(), request.size(), MSG_NOSIGNAL);
    if (res == request.size()) {
        return 0;
    }

    if (res == -1 && errno == EPIPE) {
        std::cout << "ERROR: SIGPIPE while sending request to {" << parsed_url.domain << "}" << std::endl;
        return -1;
    }

    return -2;



}



size_t get_html(char* buffer, size_t max_size, const std::string& url, const std::string& additional_params) {
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    parsed_url_t parsed_url = parse_url(url);

    if (connect_to_host(sock, parsed_url) < 0) {
        std::cout << "ERROR: Can't connect to host {" << url << "}" << std::endl;
        return 0;
    }

    if (send_request(sock, parsed_url, additional_params) != 0) {
        return 0;
    }

    size_t index = 0;
    size_t bytes_read;
    while (index < max_size) {
        bytes_read = read(
                sock,
                buffer + index,
                max_size - index
        );
        index += bytes_read;
        if (bytes_read == 0) {
            break;
        }
    }

    close(sock);

    return index;

}


