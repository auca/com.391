#ifndef ES2_TEXTURE_HPP
#define ES2_TEXTURE_HPP

#include <GL/glew.h>
#include <SDL.h>

#include "textures/texture.hpp"

namespace aur
{
    class ES2Texture : public Texture
    {
    public:
        ES2Texture(const std::vector<uint8_t> &image_data, unsigned int width, unsigned int height, unsigned int channels)
            : Texture(image_data, width, height, channels)
        {}

        ES2Texture(const ES2Texture &other) = delete;
        ES2Texture& operator=(const ES2Texture & other) = delete;

        ~ES2Texture() final
        {
            if (_texture != 0) {
                glDeleteTextures(1, &_texture);
            }
        }

        void update(unsigned int sampler) final
        {
            if (_requires_data_update) {
                glActiveTexture(GL_TEXTURE0 + sampler);
                if (_texture == 0) {
                    glGenTextures(1, &_texture);
                    glBindTexture(GL_TEXTURE_2D, _texture);
                    GLint format = _channels == 3 ? GL_RGB : GL_RGBA;
                    glTexImage2D(
                        GL_TEXTURE_2D, 0, format,
                        static_cast<GLsizei>(_width),
                        static_cast<GLsizei>(_height),
                        0, format, GL_UNSIGNED_BYTE,
                        reinterpret_cast<GLvoid *>(_image_data.data())
                    );
                } else {
                    glBindTexture(GL_TEXTURE_2D, _texture);
                    GLint format = _channels == 3 ? GL_RGB : GL_RGBA;
                    glTexSubImage2D(
                        GL_TEXTURE_2D, 0, 0, 0,
                        static_cast<GLsizei>(_width),
                        static_cast<GLsizei>(_height),
                        format, GL_UNSIGNED_BYTE,
                        reinterpret_cast<GLvoid *>(_image_data.data())
                    );
                }
                if (_mipmaps_enabled) {
                    glGenerateMipmap(GL_TEXTURE_2D);
                }
                glBindTexture(GL_TEXTURE_2D, 0);

                _requires_data_update = false;
            }

            if (_requires_params_update) {
                glActiveTexture(GL_TEXTURE0 + sampler);
                glBindTexture(GL_TEXTURE_2D, _texture);

                glTexParameteri(
                    GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    _convert_wrap_mode_to_es2_texture_wrap_mode(_wrap_mode_s)
                );
                glTexParameteri(
                    GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                    _convert_wrap_mode_to_es2_texture_wrap_mode(_wrap_mode_t)
                );
                glTexParameteri(
                    GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    _convert_filter_type_to_es2_texture_filter_type(_magnification_filter)
                );
                glTexParameteri(
                    GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    _convert_filter_type_to_es2_texture_filter_type(_minification_filter)
                );
                glTexParameterf(
                    GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, (GLfloat) _anisotropy
                );

                glBindTexture(GL_TEXTURE_2D, 0);

                _requires_params_update = false;
            }
        }

        void use(unsigned int sampler) final
        {
            if (_texture != 0) {
                glActiveTexture(GL_TEXTURE0 + sampler);
                glBindTexture(GL_TEXTURE_2D, _texture);
            }
        }

    private:
        GLuint _texture{0};

        static GLenum _convert_wrap_mode_to_es2_texture_wrap_mode(Texture::WrapMode wrap_mode)
        {
            switch (wrap_mode) {
                case Repeat:
                    return GL_REPEAT;
                case MirroredRepeat:
                    return GL_MIRRORED_REPEAT;
                case ClampToEdge:
                    return GL_CLAMP_TO_EDGE;
                default:
                    return GL_REPEAT;
            }
        }

        static GLenum _convert_filter_type_to_es2_texture_filter_type(Texture::FilterType filter)
        {
            switch (filter) {
                case Nearest:
                    return GL_NEAREST;
                case Linear:
                    return GL_LINEAR;
                case NearestMipmapNearest:
                    return GL_NEAREST_MIPMAP_NEAREST;
                case NearestMipmapLinear:
                    return GL_NEAREST_MIPMAP_LINEAR;
                case LinearMipmapNearest:
                    return GL_LINEAR_MIPMAP_NEAREST;
                case LinearMipmapLinear:
                    return GL_LINEAR_MIPMAP_LINEAR;
                default:
                    return GL_NEAREST;
            }
        }
    };
}

#endif
