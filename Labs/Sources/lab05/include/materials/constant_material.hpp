#ifndef CONSTANT_MATERIAL_HPP
#define CONSTANT_MATERIAL_HPP

#include "materials/material.hpp"
#include "textures/texture.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <string>

namespace aur {
    class ConstantMaterial : public Material {
    public:
        const glm::vec4 &get_emission_color() const {
            return _emission_color;
        }

        void set_emission_color(const glm::vec4 &emission_color) {
            _emission_color = emission_color;
        }

        float get_point_size() const {
            return _point_size;
        }

        void set_point_size(float point_size) {
            _point_size = point_size;
        }

        const std::shared_ptr<Texture> &get_texture() const {
            return _texture;
        }

        void set_texture(const std::shared_ptr<Texture> &texture) {
            _texture = texture;
        }

    protected:
        glm::vec4 _emission_color { 1.0f };
        float _point_size { 1.0f };

        std::shared_ptr<Texture> _texture;
    };
}

#endif
