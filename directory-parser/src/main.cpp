#include <iostream>
#include "directory_parser.h"

int main(int argc, char **argv) {

    std::string directory_path = argv[1];
    std::string output_file_path = argv[2];

    directory_parser(directory_path, output_file_path);

    return 0;
}