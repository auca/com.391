#ifndef RAY_HPP
#define RAY_HPP

#include "math/plane.hpp"
#include "math/sphere.hpp"

#include <glm/glm.hpp>

#include <utility>
#include <cmath>

namespace aur
{
    class Ray
    {
        typedef std::pair<bool, float> intersection_test_result_type;

    public:
        Ray(const glm::vec3 &origin, const glm::vec3 &direction) : _origin(origin), _direction(direction) { }

        [[nodiscard]] const glm::vec3 &get_origin() const
        {
            return _origin;
        }

        [[nodiscard]] const glm::vec3 &get_direction() const
        {
            return _direction;
        }

        glm::vec3 sample_point_at_distance(float distance)
        {
            return _origin + _direction * distance;
        }

        [[nodiscard]] intersection_test_result_type intersects_with_plane(const Plane &plane) const
        {
            bool intersects = false;
            float distance = 0.0f;

            float denominator = glm::dot(plane.get_normal(), _direction);
            if (fabsf(denominator) >= FLT_EPSILON) {
                float numerator = glm::dot(plane.get_normal(), _origin) + plane.get_distance();
                float quot = -(numerator / denominator);
                if (quot >= 0.0f) {
                    intersects = true;
                    distance = quot;
                }
            }

            return std::make_pair(intersects, distance);
        }

        [[nodiscard]] intersection_test_result_type intersects_with_sphere(const Sphere &sphere) const {
            bool intersects = false;
            float distance = 0.0f;

            float a = glm::dot(_direction, _direction);

            glm::vec3 origin = _origin - sphere.get_center();
            float b = 2.0f * glm::dot(_direction, origin);

            float radius = sphere.get_radius();
            float c = glm::dot(origin, origin) - radius * radius;

            float d = b * b - 4.0f * a * c;
            if (d >= 0.0f) {
                distance = (-b - sqrtf(d)) / 2.0f * a;
                if (distance < 0.0f) {
                    distance = (-b + sqrtf(d)) / 2.0f * a;
                }
                intersects = true;
            }

            return std::make_pair(intersects, distance);
        }

    private:
        glm::vec3 _origin;
        glm::vec3 _direction;
    };
}

#endif
