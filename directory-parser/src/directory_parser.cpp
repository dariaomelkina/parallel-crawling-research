#include "directory_parser.h"
#include <iostream>
#include <string>


void directory_parser(std::string &server_ip, std::string &directory_path, std::string &output_file_path) {
    std::ofstream output_file(output_file_path);
    /* Iterate through given directory */
    std::filesystem::recursive_directory_iterator end_itr;
    for (std::filesystem::recursive_directory_iterator itr(directory_path); itr != end_itr; ++itr) {
        /* Extracting path for crawling: */
        if (itr->path().extension().string() == ".html") {

            // Removing the freaking "/._" from the url. Where he heck does it come from????
            auto file_path = itr->path().string().replace(0, directory_path.length(), "");


            size_t index = 0;
            while (true) {
                // Locate the substring to replace.
                index = file_path.find("/._", index);
                if (index == std::string::npos) break;

                // Make the replacement.
                file_path.replace(index, 3, "/");

                // Advance index forward so the next iteration doesn't pick it up as well.
                index += 3;
            }

            std::cout << "Old: " << itr->path().string().replace(0, directory_path.length(), "") << std::endl;
            std::cout << "New: " << file_path << std::endl;

            output_file << "http://" << server_ip << file_path << "\n";
        }
    }
}