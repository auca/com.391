#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>
#include <sstream>
#include <fstream>

class FileUtilities {
public:
    static std::string read_text_file(const std::string& path) {
        std::ifstream file_stream(path);
        std::stringstream string_stream;
        string_stream << file_stream.rdbuf();

        return string_stream.str();
    }
};

#endif
