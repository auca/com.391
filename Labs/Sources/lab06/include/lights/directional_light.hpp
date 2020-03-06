#ifndef DIRECTIONAL_LIGHT_HPP
#define DIRECTIONAL_LIGHT_HPP

#include "lights/light.hpp"

#include <glm/glm.hpp>

namespace aur {
    class DirectionalLight : public Light {
    public:
        const glm::vec3 &get_direction() const {
            return _direction;
        }

        void set_direction(const glm::vec3 &direction) {
            _direction = direction;
            _world_direction = glm::normalize(get_world_matrix() * glm::vec4(_direction, 0.0f));
        }

        const glm::vec3 &get_world_direction() const {
            return _world_direction;
        }

    private:
        glm::vec3 _direction { 0.0f, 1.0f, 0.0f };
        glm::vec3 _world_direction { 0.0f, 1.0f, 0.0f };
    };
}

#endif
