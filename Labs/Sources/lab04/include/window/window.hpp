#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <utility>

namespace aur {
    class Window {
    public:
        Window(std::string name, unsigned int width, unsigned int height) :
            _name{std::move(name)},
            _width{width}, _height{height} {}

        virtual ~Window() = default;

        unsigned int get_width() const {
            return _width;
        }

        unsigned int get_height() const {
            return _height;
        }

        virtual void swap() = 0;

    protected:
        std::string _name;

        unsigned int _width;
        unsigned int _height;
    };
}

#endif
