#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <utility>
#include <functional>

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

        const std::function<void()> &get_on_exit() const {
            return _on_exit;
        }

        void set_on_exit(const std::function<void(void)> &on_exit) {
            _on_exit = on_exit;
        }

        const std::function<void(int)> &get_on_key() const {
            return _on_key;
        }

        void set_on_key(const std::function<void(int)> &on_key) {
            _on_key = on_key;
        }

        virtual void poll() = 0;
        virtual void swap() = 0;

    protected:
        std::string _name;

        unsigned int _width;
        unsigned int _height;

        std::function<void(void)> _on_exit;
        std::function<void(int)> _on_key;
    };
}

#endif
