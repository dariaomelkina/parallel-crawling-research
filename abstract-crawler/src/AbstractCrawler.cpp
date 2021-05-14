//
// Created by Maksym Protsyk on 5/13/21.
//


#include "AbstractCrawler.h"


void AbstractCrawler::add_url(std::string &url) {
    input_queue.emplace(std::move(url));
}

std::string AbstractCrawler::send_request(const std::string &url) {
    return get_html(url, ADDITIONAL_PARAMS);
}

bool AbstractCrawler::is_empty() {
    return output_queue.empty();
}

std::string AbstractCrawler::get_processed_item() {
    if (is_empty()) {
        throw std::runtime_error("Crawler is empty");
    }
    auto html = std::move(output_queue.front());
    output_queue.pop();
    return html;
}


const std::string AbstractCrawler::ADDITIONAL_PARAMS = "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64)"
                                                       " AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.97"
                                                       " Safari/537.36\r\n";

