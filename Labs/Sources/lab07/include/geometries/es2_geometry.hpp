#ifndef ES2_GEOMETRY_HPP
#define ES2_GEOMETRY_HPP

#include "geometries/geometry.hpp"

#include <GL/glew.h>
#include <SDL.h>

#include <string>
#include <iostream>

namespace aur
{
    class ES2Geometry : public Geometry
    {
    public:
        explicit ES2Geometry(std::vector<unsigned int> &indices, const std::vector<Vertex> &vertices)
            : Geometry(indices, vertices) {}

        ES2Geometry(const ES2Geometry &other) = delete;
        ES2Geometry& operator=(const ES2Geometry & other) = delete;

        ~ES2Geometry() final
        {
            if (_vertex_array_object != 0) {
#ifdef __APPLE__
                glDeleteVertexArraysAPPLE(1, &_vertex_array_object);
#else
                glDeleteVertexArrays(1, &_vertex_array_object);
#endif
            }

            if (_index_buffer_object != 0) {
                glDeleteBuffers(1, &_index_buffer_object);
            }

            if (_vertex_buffer_object != 0) {
                glDeleteBuffers(1, &_vertex_buffer_object);
            }
        }

        void update(const Material &material) final
        {
            if (!(_requires_indices_update || _requires_vertices_update)) {
                return;
            }

            if (_requires_indices_update) {
                if (_index_buffer_object != 0) {
                    glDeleteBuffers(1, &_index_buffer_object);
                }

                const auto *index_data = reinterpret_cast<const unsigned int *>(_indices.data());
                const size_t index_data_size{_indices.size() * sizeof(unsigned int)};

                GLuint index_buffer_object{0};
                glGenBuffers(1, &index_buffer_object);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);
                glBufferData(
                    GL_ELEMENT_ARRAY_BUFFER,
                    index_data_size, index_data,
                    _convert_usage_strategy_to_es2_buffer_usage_strategy(_indices_usage_strategy)
                );
                _index_buffer_object = index_buffer_object;
            }

            if (_requires_vertices_update) {
                if (_vertex_buffer_object != 0) {
                    glDeleteBuffers(1, &_vertex_buffer_object);
                }

                const auto *vertex_data = reinterpret_cast<const float *>(_vertices.data());
                const size_t vertex_data_size{_vertices.size() * sizeof(Vertex)};

                GLuint vertex_buffer_object{0};
                glGenBuffers(1, &vertex_buffer_object);
                glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
                glBufferData(
                    GL_ARRAY_BUFFER,
                    vertex_data_size, vertex_data,
                    _convert_usage_strategy_to_es2_buffer_usage_strategy(_vertices_usage_strategy)
                );
                _vertex_buffer_object = vertex_buffer_object;
            }

            if (_requires_indices_update || _requires_vertices_update) {
                if (_vertex_array_object != 0) {
#ifdef __APPLE__
                    glDeleteVertexArraysAPPLE(1, &_vertex_array_object);
#else
                    glDeleteVertexArrays(1, &_vertex_array_object);
#endif
                }

                GLuint vertex_array_object{0};
#ifdef __APPLE__
                glGenVertexArraysAPPLE(1, &vertex_array_object);
                glBindVertexArrayAPPLE(vertex_array_object);
#else
                glGenVertexArrays(1, &vertex_array_object);
                glBindVertexArray(vertex_array_object);
#endif
                glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_object);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer_object);

                auto &attributes = material.get_shader()->get_attributes();

                GLsizei stride = sizeof(GLfloat) * 18;

                int position_attribute_location{attributes.count("position") > 0 ? attributes.at("position") : -1};
                if (position_attribute_location != -1) {
                    glEnableVertexAttribArray(position_attribute_location);
                    glVertexAttribPointer(
                        position_attribute_location,
                        3, GL_FLOAT, GL_FALSE, stride, static_cast<const GLvoid *>(nullptr)
                    );
                }

                int color_attribute_location{attributes.count("color") > 0 ? attributes.at("color") : -1};
                if (color_attribute_location != -1) {
                    glEnableVertexAttribArray(color_attribute_location);
                    glVertexAttribPointer(
                        color_attribute_location,
                        4, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const GLvoid *>(sizeof(GLfloat) * 3)
                    );
                }

                int normal_attribute_location{attributes.count("normal") > 0 ? attributes.at("normal") : -1};
                if (normal_attribute_location != -1) {
                    glEnableVertexAttribArray(normal_attribute_location);
                    glVertexAttribPointer(
                        normal_attribute_location,
                        3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const GLvoid *>(sizeof(GLfloat) * 7)
                    );
                }

                int texture1_coordinates_attribute_location{attributes.count("texture1_coordinates") > 0 ? attributes.at("texture1_coordinates") : -1};
                if (texture1_coordinates_attribute_location != -1) {
                    glEnableVertexAttribArray(texture1_coordinates_attribute_location);
                    glVertexAttribPointer(
                        texture1_coordinates_attribute_location,
                        4, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const GLvoid *>(sizeof(GLfloat) * 10)
                    );
                }

                int texture2_coordinates_attribute_location{attributes.count("texture2_coordinates") > 0 ? attributes.at("texture2_coordinates") : -1};
                if (texture2_coordinates_attribute_location != -1) {
                    glEnableVertexAttribArray(texture2_coordinates_attribute_location);
                    glVertexAttribPointer(
                        texture2_coordinates_attribute_location,
                        4, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const GLvoid *>(sizeof(GLfloat) * 14)
                    );
                }
#ifdef __APPLE__
                glBindVertexArrayAPPLE(0);
#else
                glBindVertexArray(0);
#endif
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

                _vertex_array_object = vertex_array_object;
            }
        }

        void use() final
        {
            if (_vertex_array_object != 0) {
#ifdef __APPLE__
                glBindVertexArrayAPPLE(_vertex_array_object);
#else
                glBindVertexArray(_vertex_array_object);
#endif
            }
        }

    private:
        GLuint _vertex_array_object{0};
        GLuint _index_buffer_object{0};
        GLuint _vertex_buffer_object{0};

        static GLenum _convert_usage_strategy_to_es2_buffer_usage_strategy(Geometry::UsageStrategy usage_strategy)
        {
            switch (usage_strategy) {
                case StaticStrategy:
                    return GL_STATIC_DRAW;
                case DynamicStrategy:
                    return GL_DYNAMIC_DRAW;
                case StreamStrategy:
                    return GL_STREAM_DRAW;
                default:
                    return GL_STATIC_DRAW;
            }
        }
    };
}

#endif