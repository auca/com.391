#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/glm.hpp>

namespace aur
{
    class AABB
    {
    public:
        AABB(const glm::vec3 &minimum, const glm::vec3 &maximum)
            : _minimum(minimum), _maximum(maximum) { }

        [[nodiscard]] const glm::vec3 &get_minimum() const
        {
            return _minimum;
        }

        void set_minimum(const glm::vec3 &minimum)
        {
            if (_minimum != minimum) {
                _minimum = minimum;

                _box_was_changed = true;
            }
        }

        [[nodiscard]] const glm::vec3 &get_maximum() const
        {
            return _maximum;
        }

        void set_maximum(const glm::vec3 &maximum)
        {
            if (_maximum != maximum) {
                _maximum = maximum;

                _box_was_changed = true;
            }
        }

        [[nodiscard]] const glm::vec3 &get_center()
        {
            if (_box_was_changed) {
                _update_supporting_values();
            }

            return _center;
        }

        [[nodiscard]] const glm::vec3 &get_size()
        {
            if (_box_was_changed) {
                _update_supporting_values();
            }

            return _size;
        }

        [[nodiscard]] const glm::vec3 &get_size_halved()
        {
            if (_box_was_changed) {
                _update_supporting_values();
            }

            return _size_halved;
        }

        void transform(glm::mat4 transformation_matrix)
        {
            glm::vec4 points[] = {
                transformation_matrix * glm::vec4(_minimum, 1.0f),
                transformation_matrix * glm::vec4(_minimum.x, _minimum.y, _maximum.z, 1.0f),
                transformation_matrix * glm::vec4(_minimum.x, _maximum.y, _minimum.z, 1.0f),
                transformation_matrix * glm::vec4(_minimum.x, _maximum.y, _maximum.z, 1.0f),
                transformation_matrix * glm::vec4(_maximum.x, _minimum.y, _minimum.z, 1.0f),
                transformation_matrix * glm::vec4(_maximum.x, _minimum.y, _maximum.z, 1.0f),
                transformation_matrix * glm::vec4(_maximum.x, _maximum.y, _minimum.z, 1.0f),
                transformation_matrix * glm::vec4(_maximum, 1.0f),
            };

            _minimum.x = INFINITY;
            _minimum.y = INFINITY;
            _minimum.z = INFINITY;

            _maximum.x = -INFINITY;
            _maximum.y = -INFINITY;
            _maximum.z = -INFINITY;

            for (auto point : points) {
                if (_minimum.x > point.x) {
                    _minimum.x = point.x;
                }
                if (_minimum.y > point.y) {
                    _minimum.y = point.y;
                }
                if (_minimum.z > point.z) {
                    _minimum.z = point.z;
                }

                if (_maximum.x < point.x) {
                    _maximum.x = point.x;
                }
                if (_maximum.y < point.y) {
                    _maximum.y = point.y;
                }
                if (_maximum.z < point.z) {
                    _maximum.z = point.z;
                }
            }

            _box_was_changed = true;
        }

    private:
        glm::vec3 _minimum;
        glm::vec3 _maximum;

        glm::vec3 _center{0.0f};

        glm::vec3 _size{0.0f};
        glm::vec3 _size_halved{0.0f};

        bool _box_was_changed{false};

        void _update_supporting_values()
        {
            _center = _maximum + _minimum * 0.5f;
            _size = _maximum - _minimum;
            _size_halved = _size * 0.5f;

            _box_was_changed = false;
        }
    };
}

#endif
