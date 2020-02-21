#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "materials/material.hpp"
#include "geometries/vertex.hpp"

#include <vector>
#include <utility>

#include <glm/glm.hpp>

namespace aur {
    class Geometry {
    public:
        explicit Geometry(std::vector<unsigned int> indices, std::vector<Vertex> vertices)
            : _indices(std::move(indices)), _vertices(std::move(vertices)) {}

        virtual ~Geometry() = default;

        int get_type() const {
            return _type;
        }

        void set_type(int type) {
            _type = type;
        }

        float get_line_width() const {
            return _line_width;
        }

        void set_line_width(float lineWidth) {
            _line_width = lineWidth;
        }

        const std::vector<unsigned int> &get_indices() const {
            return _indices;
        }

        const std::vector<Vertex> &get_vertices() const {
            return _vertices;
        }

        void transform(glm::mat4 transformation_matrix) {
            for (auto &vertex : _vertices) {
                vertex.position = glm::vec3(transformation_matrix * glm::vec4(vertex.position, 1.0f));
            }
        }

        virtual void update(const Material &material) = 0;

        virtual void bind() = 0;

    protected:
        int _type { 0x0004 };
        float _line_width { 1.0f };

        std::vector<unsigned int> _indices;
        std::vector<Vertex> _vertices;
    };
}

#endif
