#ifndef PLANE_HPP
#define PLANE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>

namespace aur
{
    class Plane
    {
    public:
        Plane(const glm::vec3 &normal, float distance) : _normal(normal), _distance(distance) {}

        [[nodiscard]] const glm::vec3 &get_normal() const
        {
            return _normal;
        }

        [[nodiscard]] float get_distance() const
        {
            return _distance;
        }

        void transform(glm::mat4 transformation_matrix)
        {
            glm::mat3 normal_matrix = glm::inverseTranspose(glm::mat3(transformation_matrix));
            glm::vec3 normal = normal_matrix * _normal;

            glm::vec4 coplanar_point = glm::vec4(_normal * -_distance, 1.0f);
            coplanar_point = transformation_matrix * coplanar_point;

            _normal = normal;
            _distance = -glm::dot(glm::vec3(coplanar_point), normal);
        }

    private:
        glm::vec3 _normal;
        float _distance;
    };
}

#endif
