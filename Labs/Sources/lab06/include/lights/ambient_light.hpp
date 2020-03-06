#ifndef AMBIENT_LIGHT_HPP
#define AMBIENT_LIGHT_HPP

#include <glm/glm.hpp>

namespace aur {
    class AmbientLight {
    public:
        explicit AmbientLight(const glm::vec3 &ambient_color = { 0.07f, 0.07f, 0.07f })
            : _ambient_color(ambient_color) { }

        const glm::vec3 &get_ambient_color() const {
            return _ambient_color;
        }

        void set_ambient_color(const glm::vec3 &ambient_color) {
            _ambient_color = ambient_color;
        }

    private:
        glm::vec3 _ambient_color { 0.0f };
    };
}

#endif
