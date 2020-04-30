#ifndef MESH_HPP
#define MESH_HPP

#include "objects/object.hpp"
#include "geometries/geometry.hpp"
#include "materials/material.hpp"

#include <memory>
#include <utility>

namespace aur
{
    class Mesh : public Object
    {
    public:
        Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material,
             const glm::vec3 &position = glm::vec4(0.0f),
             const glm::vec3 &rotation = glm::vec4(0.0f),
             const glm::vec3 &scale = glm::vec4(1.0f),
             std::weak_ptr<Object> parent = {})
            : Object("untitled mesh", position, rotation, scale, std::move(parent)),
              _geometry{std::move(geometry)},
              _material{std::move(material)}
        {}

        const std::shared_ptr<Geometry> &get_geometry() const
        {
            return _geometry;
        }

        const std::shared_ptr<Material> &get_material() const
        {
            return _material;
        }

    private:
        std::shared_ptr<Geometry> _geometry;
        std::shared_ptr<Material> _material;
    };
}

#endif
