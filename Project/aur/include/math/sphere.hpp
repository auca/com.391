#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/glm.hpp>

namespace aur
{
    class Sphere
    {
    public:
        Sphere(const glm::vec3 &center, float radius)
            : _center(center), _radius(radius) { }

        [[nodiscard]] const glm::vec3 &get_center() const
        {
            return _center;
        }

        [[nodiscard]] float get_radius() const
        {
            return _radius;
        }

        void transform(glm::mat4 transformation_matrix)
        {
            _center = glm::vec3(transformation_matrix * glm::vec4(_center, 1.0f));

            float squared_scale_x =
                transformation_matrix[0][0] * transformation_matrix[0][0] +
                transformation_matrix[0][1] * transformation_matrix[0][1] +
                transformation_matrix[0][2] * transformation_matrix[0][2];

            float squared_scale_y =
                transformation_matrix[1][0] * transformation_matrix[1][0] +
                transformation_matrix[1][1] * transformation_matrix[1][1] +
                transformation_matrix[1][2] * transformation_matrix[1][2];

            float squared_scale_z =
                transformation_matrix[2][0] * transformation_matrix[2][0] +
                transformation_matrix[2][1] * transformation_matrix[2][1] +
                transformation_matrix[2][2] * transformation_matrix[2][2];

            float scale = sqrtf(fmaxf(squared_scale_x, fmaxf(squared_scale_y, squared_scale_z)));
            _radius *= scale;
        }

    private:
        glm::vec3 _center;
        float _radius;
    };
}

#endif
