#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <utility>
#include <functional>

namespace aur
{
    class Window
    {
    public:
        Window(std::string name, unsigned int width, unsigned int height) :
            _name{std::move(name)},
            _width{width}, _height{height}
        {}

        virtual ~Window() = default;

        [[nodiscard]] unsigned int get_width() const
        {
            return _width;
        }

        [[nodiscard]] unsigned int get_height() const
        {
            return _height;
        }

        [[nodiscard]] const std::function<void()> &get_on_exit() const
        {
            return _on_exit;
        }

        void set_on_exit(const std::function<void(void)> &on_exit)
        {
            _on_exit = on_exit;
        }

        [[nodiscard]] const std::function<void(int)> &get_on_key_down() const
        {
            return _on_key_down;
        }

        void set_on_key_down(const std::function<void(int)> &on_key_down)
        {
            _on_key_down = on_key_down;
        }

        [[nodiscard]] const std::function<void(int, int, int, int)> &get_on_mouse_move() const
        {
            return _on_mouse_move;
        }

        void set_on_mouse_move(const std::function<void(int, int, int, int)> &on_mouse_move)
        {
            _on_mouse_move = on_mouse_move;
        }

        [[nodiscard]] const std::function<void(int, int, int)> &get_on_mouse_down() const
        {
            return _on_mouse_down;
        }

        void set_on_mouse_down(const std::function<void(int, int, int)> &on_mouse_down)
        {
            _on_mouse_down = on_mouse_down;
        }

        virtual void poll() = 0;

        virtual void swap() = 0;

    protected:
        std::string _name;

        unsigned int _width;
        unsigned int _height;

        std::function<void(void)> _on_exit;
        std::function<void(int)> _on_key_down;
        std::function<void(int, int, int, int)> _on_mouse_move;
        std::function<void(int, int, int)> _on_mouse_down;
    };
}

#endif
