#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>

namespace aur {
    class FileUtilities {
    public:
        static std::string read_text_file(const std::string &path) {
            std::ifstream file_stream{path};
            if (!file_stream.is_open()) {
                std::cerr << "Failed to open the file: '" << path << "'" << std::endl;
                exit(-1);
            }

            std::stringstream string_stream;
            string_stream << file_stream.rdbuf();

            return string_stream.str();
        }
    };
}

#endif
