#ifndef ES2_GEOMETRY_HPP
#define ES2_GEOMETRY_HPP

#include "geometries/geometry.hpp"

#include <GL/glew.h>
#include <SDL.h>

#include <string>
#include <iostream>

namespace aur {
    class ES2Geometry : public Geometry {
    public:
        explicit ES2Geometry(std::vector<unsigned int> &indices, const std::vector<Vertex> &vertices)
            : Geometry(indices, vertices) { }

        void update(const Material &material) final {
            GLuint vertex_array_object { 0 };
            GLuint index_buffer_object { 0 };
            GLuint vertex_buffer_object { 0 };

            const auto *index_data = reinterpret_cast<const unsigned int *>(_indices.data());
            const size_t index_data_size = _indices.size() * sizeof(unsigned int);

            glGenBuffers(1, &index_buffer_object);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);
            glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                index_data_size, index_data,
                GL_STATIC_DRAW
            );

            const auto *vertex_data = reinterpret_cast<const float *>(_vertices.data());
            const size_t vertex_data_size = _vertices.size() * sizeof(Vertex);

            glGenBuffers(1, &vertex_buffer_object);
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
            glBufferData(
                GL_ARRAY_BUFFER,
                vertex_data_size, vertex_data,
                GL_STATIC_DRAW
            );

#ifdef __APPLE__
            glGenVertexArraysAPPLE(1, &vertex_array_object);
            glBindVertexArrayAPPLE(vertex_array_object);
#else
            glGenVertexArrays(1, &vertex_array_object);
            glBindVertexArray(vertex_array_object);
#endif
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);

            int position_attribute_location{material.get_shader()->get_attributes().at("position")};
            int color_attribute_location{material.get_shader()->get_attributes().at("color")};
            int normal_attribute_location{material.get_shader()->get_attributes().at("normal")};
            int texture_coordinates_attribute_location{material.get_shader()->get_attributes().at("texture_coordinates")};

            GLsizei stride = sizeof(GLfloat) * 14;
            if (position_attribute_location != -1) {
                glEnableVertexAttribArray(position_attribute_location);
                glVertexAttribPointer(
                    position_attribute_location,
                    3, GL_FLOAT, GL_FALSE, stride, (const GLvoid *) 0
                );
            }

            if (color_attribute_location != -1) {
                glEnableVertexAttribArray(color_attribute_location);
                glVertexAttribPointer(
                    color_attribute_location,
                    4, GL_FLOAT, GL_FALSE, stride, (const GLvoid *) (sizeof(GLfloat) * 3)
                );
            }

            if (normal_attribute_location != -1) {
                glEnableVertexAttribArray(normal_attribute_location);
                glVertexAttribPointer(
                    normal_attribute_location,
                    3, GL_FLOAT, GL_FALSE, stride, (const GLvoid *) (sizeof(GLfloat) * 7)
                );
            }

            if (texture_coordinates_attribute_location != -1) {
                glEnableVertexAttribArray(texture_coordinates_attribute_location);
                glVertexAttribPointer(
                    texture_coordinates_attribute_location,
                    4, GL_FLOAT, GL_FALSE, stride, (const GLvoid *) (sizeof(GLfloat) * 10)
                );
            }
#ifdef __APPLE__
            glBindVertexArrayAPPLE(0);
#else
            glBindVertexArray(0);
#endif
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            _vertex_array_object = vertex_array_object;
        }

        void bind() final {
#ifdef __APPLE__
            glBindVertexArrayAPPLE(_vertex_array_object);
#else
            glBindVertexArray(_vertex_array_object);
#endif
        }

    private:
        int _vertex_array_object { 0 };
    };
}

#endif
