#ifndef SDL_WINDOW_HPP
#define SDL_WINDOW_HPP

#include "window.hpp"

#include <GL/glew.h>
#include <SDL.h>

class SDLWindow : public Window {
public:
    SDLWindow(const std::string &name, int width, int height)
        : Window { name, width, height } {
        SDL_Init(SDL_INIT_VIDEO);

        _window =
            SDL_CreateWindow(
                name.c_str(),
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                width, height,
                SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
            );
        SDL_GL_GetDrawableSize(_window, &_width, &_height);

        _gl_context = SDL_GL_CreateContext(_window);
        glewExperimental = GL_TRUE; glewInit();

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

        if (SDL_GL_SetSwapInterval(-1) < 0) {
            SDL_GL_SetSwapInterval(1);
        }
    }

    void swap() final {
        SDL_GL_SwapWindow(_window);
    }

    ~SDLWindow() final {
        SDL_GL_DeleteContext(_gl_context);
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }

private:
    SDL_GLContext _gl_context;
    SDL_Window *_window;
};

#endif
