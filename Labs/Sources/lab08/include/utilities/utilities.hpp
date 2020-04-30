#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <SDL_image.h>

#include <tuple>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>

namespace aur::file_utilities
{
    typedef std::tuple<std::vector<uint8_t>, unsigned int, unsigned int, unsigned int> image_data_type;

    std::string read_text_file(const std::string &path)
    {
        std::ifstream file_stream{path};
        if (!file_stream.is_open()) {
            std::cerr << "Failed to open the file: '" << path << "'" << std::endl;
            exit(-1);
        }

        std::stringstream string_stream;
        string_stream << file_stream.rdbuf();

        return string_stream.str();
    }

    image_data_type read_image_file(const std::string &path)
    {
        SDL_Surface *surface = IMG_Load(path.c_str());
        if (!surface) {
            std::cerr << "Failed to open the file: '" << path << "'" << std::endl;
            exit(-1);
        }

        auto bytes_per_pixel = surface->format->BytesPerPixel;
        if (!(bytes_per_pixel == 3 || bytes_per_pixel == 4))
        {
            std::cerr << "Invalid image file format (only RGB and RGBA files are supported): '" << path << "'" << std::endl;
            exit(-1);
        }

        auto *data = static_cast<uint8_t *>(surface->pixels);
        std::vector<uint8_t> image_data;
        for (int y = surface->h - 1; y >= 0; --y) { // flip the image for the OpenGL coordinate system
            for (int x = 0; x < surface->w; ++x) {
                for (int i = 0; i < bytes_per_pixel; ++i) {
                    image_data.push_back(*(data + y * surface->pitch + x * bytes_per_pixel + i));
                }
            }
        }
        SDL_FreeSurface(surface);

        return std::make_tuple(image_data, surface->w, surface->h, bytes_per_pixel);
    }
}

#endif
