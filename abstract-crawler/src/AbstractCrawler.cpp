//
// Created by Maksym Protsyk on 5/13/21.
//


#include "AbstractCrawler.h"
#include "iostream"


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
    for (size_t j = 0; j < 8; j++) {
        std::vector<std::pair<size_t, size_t>> indeces;
        std::vector<std::string> tag_names;

        std::stack<std::pair<std::string, size_t>> tags;

        bool in_tag_name = false;
        bool in_closing_tag = false;
        size_t tag_start = 0;


        for (size_t i = 0; i < html_size - 2; i++) {
            if (in_tag_name) {
                if (html[i] == '>' || html[i] == ' ') {
                    std::string current_tag;
                    in_tag_name = false;
                    current_tag.append(html + tag_start + 1, i - tag_start - 1);
                    tags.emplace(current_tag, tag_start);
                }
                else if (html[i] == '/' && html[i+1] == '>') {
                    std::string current_tag;
                    in_tag_name = false;
                    indeces.emplace_back(tag_start, i+1);
                    current_tag.append(html + tag_start + 1, i - tag_start - 1);
                    tag_names.emplace_back(std::move(current_tag));
                }
                continue;
            }

            if (in_closing_tag) {
                if (html[i] == '>' ) {
                    auto closed_tag = std::move(tags.top());
                    tags.pop();
                    indeces.emplace_back(closed_tag.second, i);
                    tag_names.emplace_back(std::move(closed_tag.first));
                    in_closing_tag = false;
                }
                continue;
            }



            if (html[i] == '<') {
                if (html[i + 1] == '/') {
                    in_closing_tag = true;
                }
                else {
                    in_tag_name = true;
                    tag_start = i;
                }

            }


        }
        if (j > 0) {
            continue;
        }


    }



    return 0;


}

void AbstractCrawler::add_from_file(const std::string& filename, int64_t num_websites) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open file");
    }
    int64_t counter = 0; // to add a specific number of websites
    std::string word;
    while(file >> word){
        if (counter == num_websites) {
            break;
        }
        add_url(word);
        counter++;
    }

    // if there is less than num_websites urls in the file, notify the user
    if (counter < num_websites) {
        std::cout << "Added only " << counter << " websites from desired " << num_websites << " websites" << std::endl;
    }
}



const std::string AbstractCrawler::ADDITIONAL_PARAMS = "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64)"
                                                       " AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.97"
                                                       " Safari/537.36\r\n";

