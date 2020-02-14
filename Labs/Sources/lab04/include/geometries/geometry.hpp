#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "materials/material.hpp"

#include <vector>
#include <utility>

#include <glm/glm.hpp>

namespace aur {
    struct Vertex {
        glm::vec3 position{0.0f};
        glm::vec4 color{1.0f};
    };

    class Geometry {
    public:
        explicit Geometry(std::vector<Vertex> vertices) :
            _vertices(std::move(vertices)) {}

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

        const std::vector<Vertex> &get_vertices() const {
            return _vertices;
        }

        virtual void update(const Material &material) = 0;

        virtual void bind() = 0;

    protected:
        int _type{0x0004};
        float _line_width{1.0f};

        std::vector<Vertex> _vertices;
    };
}

#endif
