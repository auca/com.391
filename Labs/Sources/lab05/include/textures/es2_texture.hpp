#ifndef ES2_TEXTURE_HPP
#define ES2_TEXTURE_HPP

#include <GL/glew.h>
#include <SDL.h>

#include "textures/texture.hpp"

namespace aur {
    class ES2Texture : public Texture {
    public:
        ES2Texture(const std::vector<uint8_t> &image_data, unsigned int width, unsigned int height, unsigned int channels)
            : Texture(image_data, width, height, channels) {
            GLuint texture { 0 };
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            GLint format = _channels == 3 ? GL_RGB : GL_RGBA;
            glTexImage2D(
                GL_TEXTURE_2D, 0, format,
                static_cast<GLsizei>(_width),
                static_cast<GLsizei>(_height),
                0, format, GL_UNSIGNED_BYTE,
                reinterpret_cast<GLvoid *>(_image_data.data())
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);
            _texture = texture;
        }

        ~ES2Texture() final {
            auto texture = static_cast<GLuint>(_texture);
            glDeleteTextures(1, &texture);
        }

        void update() final {
            if (_requires_update) {
                glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(_texture));
                GLint format = _channels == 3 ? GL_RGB : GL_RGBA;
                glTexSubImage2D(
                    GL_TEXTURE_2D, 0, 0, 0,
                    static_cast<GLsizei>(_width),
                    static_cast<GLsizei>(_height),
                    format, GL_UNSIGNED_BYTE,
                    reinterpret_cast<GLvoid *>(_image_data.data())
                );
                glBindTexture(GL_TEXTURE_2D, 0);

                _requires_update = false;
            }
        }

        void use() final {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(_texture));
        }
    };
}

#endif
