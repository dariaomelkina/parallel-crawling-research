//
// Created by Maksym Protsyk on 5/13/21.
//


#include "AbstractCrawler.h"


void AbstractCrawler::add_url(const std::string &url) {
    input_queue.emplace_back(url);
}

int AbstractCrawler::get_socket(const std::string &url) {
    return send_request(url, ADDITIONAL_PARAMS);
}

bool AbstractCrawler::is_empty() {
    return output_queue.empty();
}

std::string AbstractCrawler::get_processed_item() {
    if (is_empty()) {
        throw std::runtime_error("Crawler is empty");
    }
    auto html = std::move(output_queue.front());
    output_queue.pop_front();
    return html;
}


size_t AbstractCrawler::count_tags(const char *html, size_t html_size) {
    if (html_size <= 1) {
        return 0;
    }
    size_t tags = 0;
    bool in_tag = false;
    for (size_t i = 0; i < html_size - 1; i++) {
        if (!in_tag) {
            if (html[i] == '<' && html[i+1] != '/' && html[i+1] != '!') {
                tags += 1;
                in_tag = true;
            }
        } else {
            if (html[i] == '>') {
                in_tag = false;
            }
        }
    }

    return tags;

}


const std::string AbstractCrawler::ADDITIONAL_PARAMS = "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64)"
                                                       " AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.97"
                                                       " Safari/537.36\r\n";

