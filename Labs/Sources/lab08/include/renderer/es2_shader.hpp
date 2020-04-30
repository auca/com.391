#ifndef ES2_SHADER_HPP
#define ES2_SHADER_HPP

#include "renderer/shader.hpp"

#include <GL/glew.h>
#include <SDL.h>

#include <iostream>
#include <cstdlib>

namespace aur
{
    class ES2Shader final : public Shader
    {
    public:
        ES2Shader(const std::string &vertex_shader_source, const std::string &fragment_shader_source,
                  const std::vector<std::string> &attributes, const std::vector<std::string> &uniforms)
            : Shader(vertex_shader_source, fragment_shader_source, attributes, uniforms)
        {}

        ES2Shader(const ES2Shader &other) = delete;
        ES2Shader& operator=(const ES2Shader & other) = delete;

        ~ES2Shader() final
        {
            if (_program != -1) {
                glDeleteProgram(_program);
            }
        }

        void compile() final
        {
            cleanup();

            int vertex_shader_object = _compile_shader(GL_VERTEX_SHADER);
            if (vertex_shader_object == -1) {
                _dead = true;
                return;
            }

            int fragment_shader_object = _compile_shader(GL_FRAGMENT_SHADER);
            if (fragment_shader_object == -1) {
                _dead = true;
                return;
            }

            int shader_program = _link_shader(vertex_shader_object, fragment_shader_object);
            if (shader_program == -1) {
                _dead = true;
                return;
            }

            _program = shader_program;
        }

        void cleanup() final
        {
            if (_program != -1) {
                glDeleteProgram(_program);
            }
            _program = -1;
            _dead = false;
        }

        void use() final
        {
            if (_program != -1) {
                glUseProgram(_program);
            }
        }

    private:
        int _compile_shader(int shader_type)
        {
            const char *shader_source =
                shader_type == GL_VERTEX_SHADER ?
                    _vertex_shader_source.c_str() :
                    _fragment_shader_source.c_str();

            GLuint shader_object = glCreateShader(shader_type);
            glShaderSource(shader_object, 1, (const GLchar **) &shader_source, nullptr);
            glCompileShader(shader_object);

            GLint status;
            glGetShaderiv(shader_object, GL_COMPILE_STATUS, &status);
            if (status == GL_FALSE) {
                GLint info_log_length;
                glGetShaderiv(shader_object, GL_INFO_LOG_LENGTH, &info_log_length);
                if (info_log_length > 0) {
                    auto *info_log = new GLchar[info_log_length];

                    glGetShaderInfoLog(shader_object, info_log_length, nullptr, info_log);
                    std::cerr << "Failed to compile a vertex shader" << std::endl
                              << "Compilation log:\n" << info_log << std::endl << std::endl;

                    delete[] info_log;
                }
                return _program = -1;
            }

            return shader_object;
        }

        int _link_shader(int vertex_shader_object, int fragment_shader_object)
        {
            GLuint shader_program = glCreateProgram();
            glAttachShader(shader_program, vertex_shader_object);
            glAttachShader(shader_program, fragment_shader_object);
            glLinkProgram(shader_program);

            GLint status;
            glGetProgramiv(shader_program, GL_LINK_STATUS, &status);
            if (status == GL_FALSE) {
                GLint info_log_length;
                glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &info_log_length);
                if (info_log_length > 0) {
                    auto *info_log = new GLchar[info_log_length];

                    glGetProgramInfoLog(shader_program, info_log_length, nullptr, info_log);
                    std::cerr << "Failed to link a shader program" << std::endl
                              << "Linker log:\n" << info_log << std::endl << std::endl;

                    delete[] info_log;
                }
                return _program = -1;
            }

            glDetachShader(shader_program, vertex_shader_object);
            glDetachShader(shader_program, fragment_shader_object);
            glDeleteShader(vertex_shader_object);
            glDeleteShader(fragment_shader_object);

            for (auto const &attribute : _attributes) {
                _attributes[attribute.first] = glGetAttribLocation(shader_program, attribute.first.c_str());
            }
            for (auto const &uniform : _uniforms) {
                _uniforms[uniform.first] = glGetUniformLocation(shader_program, uniform.first.c_str());
            }

            return shader_program;
        }
    };
}

#endif
