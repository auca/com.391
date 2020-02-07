#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <utility>

class Window {
public:
    Window(std::string name, int width, int height) :
        _name { std::move(name) },
        _width { width }, _height { height } { }

    virtual ~Window() = default;

    int get_width() const {
        return _width;
    }

    int get_height() const {
        return _height;
    }

    virtual void swap() = 0;

protected:
    std::string _name;

    int _width;
    int _height;
};

#endif
