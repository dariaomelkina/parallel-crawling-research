#include <iostream>
#include <filesystem>
#include <fstream>

int main(int argc, char **argv) {

    std::string directory_path = "/Users/dashaomelkina/acs/parallel-crawling-research/directory-parser/sample";
    std::string output_file_path = "";

    std::ofstream output_file("test.txt");

    /* Iterate through given directory */
    std::filesystem::recursive_directory_iterator end_itr;
    for (std::filesystem::recursive_directory_iterator itr(directory_path); itr != end_itr; ++itr) {
        /* Extracting path for crawling: */
        if (itr->path().extension().string() == ".html") {
            output_file << itr->path().string().replace(0, directory_path.length(), "") << "\n";
        }
    }

    return 0;
}