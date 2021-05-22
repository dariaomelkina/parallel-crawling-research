#include "directory_parser.h"

void directory_parser(std::string &server_ip, std::string &directory_path, std::string &output_file_path) {
    std::ofstream output_file(output_file_path);
    /* Iterate through given directory */
    std::filesystem::recursive_directory_iterator end_itr;
    for (std::filesystem::recursive_directory_iterator itr(directory_path); itr != end_itr; ++itr) {
        /* Extracting path for crawling: */
        if (itr->path().extension().string() == ".html") {
            output_file << "http://" << server_ip << itr->path().string().replace(0, directory_path.length(), "") << "\n";
        }
    }
}