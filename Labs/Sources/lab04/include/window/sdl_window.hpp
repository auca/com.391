#ifndef SDL_WINDOW_HPP
#define SDL_WINDOW_HPP

#include "window/window.hpp"

#include <GL/glew.h>
#include <SDL.h>

namespace aur {
    class SDLWindow : public Window {
    public:
        SDLWindow(const std::string &name, unsigned int width, unsigned int height, bool msaa_enabled = true,
                  int msaa_samples = 16)
            : Window{name, width, height} {
            SDL_Init(SDL_INIT_VIDEO);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
            if (msaa_enabled) {
                SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
                SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, msaa_samples);
            }

            _window =
                SDL_CreateWindow(
                    name.c_str(),
                    SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED,
                    static_cast<int>(width),
                    static_cast<int>(height),
                    static_cast<unsigned int>(SDL_WINDOW_OPENGL) | static_cast<unsigned int>(SDL_WINDOW_ALLOW_HIGHDPI)
                );
            SDL_GL_GetDrawableSize(_window, reinterpret_cast<int *>(&_width), reinterpret_cast<int *>(&_height));

            _gl_context = SDL_GL_CreateContext(_window);
            glewInit();

            if (SDL_GL_SetSwapInterval(-1) < 0) {
                SDL_GL_SetSwapInterval(1);
            }
        }

        ~SDLWindow() final {
            SDL_GL_DeleteContext(_gl_context);
            SDL_DestroyWindow(_window);
            SDL_Quit();
        }

        void swap() final {
            SDL_GL_SwapWindow(_window);
        }

    private:
        SDL_GLContext _gl_context;
        SDL_Window *_window;
    };
}

#endif
