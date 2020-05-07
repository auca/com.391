#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "materials/material.hpp"
#include "geometries/vertex.hpp"

#include <vector>
#include <utility>

#include <glm/glm.hpp>

namespace aur
{
    class Geometry
    {
    public:
        enum Type
        {
            Points,
            Lines,
            LineLoop,
            LineStrip,
            Triangles,
            TriangleFan,
            TriangleStrip
        };

        enum UsageStrategy
        {
            StaticStrategy,
            DynamicStrategy,
            StreamStrategy
        };

        explicit Geometry(std::vector<unsigned int> indices, std::vector<Vertex> vertices)
            : _indices(std::move(indices)), _vertices(std::move(vertices))
        {}

        virtual ~Geometry() = default;

        [[nodiscard]] Type get_type() const
        {
            return _type;
        }

        void set_type(Type type)
        {
            _type = type;
        }

        [[nodiscard]] const std::vector<unsigned int> &get_indices() const
        {
            return _indices;
        }

        [[nodiscard]] const std::vector<Vertex> &get_vertices() const
        {
            return _vertices;
        }

        [[nodiscard]] UsageStrategy get_vertices_usage_strategy() const
        {
            return _vertices_usage_strategy;
        }

        void set_vertices_usage_strategy(UsageStrategy vertices_usage_strategy)
        {
            if (_vertices_usage_strategy != vertices_usage_strategy) {
                _vertices_usage_strategy = vertices_usage_strategy;
                _requires_vertices_update = true;
            }
        }

        [[nodiscard]] UsageStrategy get_indices_usage_strategy() const
        {
            return _indices_usage_strategy;
        }

        void set_indices_usage_strategy(UsageStrategy indices_usage_strategy)
        {
            if (_indices_usage_strategy != indices_usage_strategy) {
                _indices_usage_strategy = indices_usage_strategy;
                _requires_indices_update = true;
            }
        }

        [[nodiscard]] float get_line_width() const
        {
            return _line_width;
        }

        void set_line_width(float lineWidth)
        {
            _line_width = lineWidth;
        }

        void transform(glm::mat4 transformation_matrix)
        {
            for (auto &vertex : _vertices) {
                vertex.position = glm::vec3(transformation_matrix * glm::vec4(vertex.position, 1.0f));
            }
            _requires_vertices_update = true;
        }

        virtual void update(const Material &material) = 0;

        virtual void use() = 0;

    protected:
        Type _type{Triangles};

        std::vector<unsigned int> _indices;
        std::vector<Vertex> _vertices;
        bool _requires_indices_update{true};
        bool _requires_vertices_update{true};

        UsageStrategy _vertices_usage_strategy{StaticStrategy};
        UsageStrategy _indices_usage_strategy{StaticStrategy};

        float _line_width{1.0f};
    };
}

#endif
