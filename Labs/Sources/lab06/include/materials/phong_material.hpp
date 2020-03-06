#ifndef PHONG_MATERIAL_HPP
#define PHONG_MATERIAL_HPP

#include "materials/material.hpp"
#include "textures/texture.hpp"

#include <glm/glm.hpp>

namespace aur {
    class PhongMaterial : public Material {
    public:
        const glm::vec3 &get_ambient_color() const {
            return _ambient_color;
        }

        void set_ambient_color(const glm::vec3 &ambient_color) {
            _ambient_color = ambient_color;
        }

        const glm::vec4 &get_diffuse_color() const {
            return _diffuse_color;
        }

        void set_diffuse_color(const glm::vec4 &diffuse_color) {
            _diffuse_color = diffuse_color;
        }

        const glm::vec4 &get_emission_color() const {
            return _emission_color;
        }

        void set_emission_color(const glm::vec4 &emission_color) {
            _emission_color = emission_color;
        }

        const glm::vec3 &get_specular_color() const {
            return _specular_color;
        }

        void set_specular_color(const glm::vec3 &specular_color) {
            _specular_color = specular_color;
        }

        float get_specular_exponent() const {
            return _specular_exponent;
        }

        void set_specular_exponent(float specular_exponent) {
            _specular_exponent = specular_exponent;
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
        glm::vec3 _ambient_color { 0.0f };
        glm::vec4 _diffuse_color { 1.0f };
        glm::vec4 _emission_color { 0.0f };

        glm::vec3 _specular_color { 1.0f };
        float _specular_exponent { 1.0f };

        float _point_size { 1.0f };

        std::shared_ptr<Texture> _texture;
    };
}

#endif
