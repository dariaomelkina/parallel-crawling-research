#include <iostream>
#include "directory_parser.h"

int main(int argc, char **argv) {

    std::string server_ip = argv[1];
    std::string directory_path = argv[2];
    std::string output_file_path = argv[3];

    directory_parser(server_ip, directory_path, output_file_path);

    return 0;
}