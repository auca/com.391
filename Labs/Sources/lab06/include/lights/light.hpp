#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "objects/object.hpp"

#include <glm/glm.hpp>

namespace aur {
    class Light : public Object {
    public:
        bool is_enabled() const {
            return _enabled;
        }

        void set_enabled(bool enabled) {
            _enabled = enabled;
        }

        const glm::vec3 &get_ambient_color() const {
            return _ambient_color;
        }

        void set_ambient_color(const glm::vec3 &ambient_color) {
            _ambient_color = ambient_color;
        }

        const glm::vec3 &get_diffuse_color() const {
            return _diffuse_color;
        }

        void set_diffuse_color(const glm::vec3 &diffuse_color) {
            _diffuse_color = diffuse_color;
        }

        const glm::vec3 &get_specular_color() const {
            return _specular_color;
        }

        void set_specular_color(const glm::vec3 &specular_color) {
            _specular_color = specular_color;
        }

        float get_intensity() const {
            return _intensity;
        }

        void set_intensity(float intensity) {
            _intensity = intensity;
        }

        bool is_two_sided() const {
            return _two_sided;
        }

        void set_two_sided(bool two_sided) {
            _two_sided = two_sided;
        }

    private:
        bool _enabled { true };

        glm::vec3 _ambient_color { 0.0f };
        glm::vec3 _diffuse_color { 1.0f };
        glm::vec3 _specular_color { 1.0f };

        float _intensity { 1.0f };

        bool _two_sided { false };
    };
}

#endif
