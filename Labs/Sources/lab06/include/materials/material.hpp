#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "renderer/shader.hpp"
#include "scene/scene.hpp"
#include "objects/mesh.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace aur {
    class Mesh;

    class Material {
    public:
        const std::shared_ptr<Shader> &get_shader() const {
            return _shader;
        }

        virtual ~Material() = default;

        virtual void update(std::shared_ptr<Scene> scene, std::shared_ptr<Mesh> mesh) = 0;

        virtual void use() = 0;

    protected:
        std::shared_ptr<Shader> _shader;
    };
}

#endif
