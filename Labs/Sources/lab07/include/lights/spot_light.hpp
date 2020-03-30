#ifndef SPOT_LIGHT_HPP
#define SPOT_LIGHT_HPP

#include "lights/light.hpp"

namespace aur
{
    class SpotLight : public Light
    {
    public:
        float get_attenuation_distance() const
        {
            return _attenuation_distance;
        }

        void set_attenuation_distance(float attenuation_distance)
        {
            _attenuation_distance = attenuation_distance;
        }

        bool is_use_constant_linear_quadratic_attenuation() const
        {
            return _use_constant_linear_quadratic_attenuation;
        }

        void set_use_constant_linear_quadratic_attenuation(bool use_constant_linear_quadratic_attenuation)
        {
            _use_constant_linear_quadratic_attenuation = use_constant_linear_quadratic_attenuation;
        }

        float get_constant_attenuation() const
        {
            return _constant_attenuation;
        }

        void set_constant_attenuation(float constant_attenuation)
        {
            _constant_attenuation = constant_attenuation;
        }

        float get_linear_attenuation() const
        {
            return _linear_attenuation;
        }

        void set_linear_attenuation(float linear_attenuation)
        {
            _linear_attenuation = linear_attenuation;
        }

        float get_quadratic_attenuation() const
        {
            return _quadratic_attenuation;
        }

        void set_quadratic_attenuation(float quadratic_attenuation)
        {
            _quadratic_attenuation = quadratic_attenuation;
        }

        float get_culling_range() const
        {
            return _culling_range;
        }

        void set_culling_range(float culling_range)
        {
            _culling_range = culling_range;
        }

        const glm::vec3 &get_direction() const
        {
            return _direction;
        }

        void set_direction(const glm::vec3 &direction)
        {
            _direction = direction;
            _world_direction = glm::vec3(glm::normalize(get_world_matrix() * glm::vec4(_direction, 0.0f)));
        }

        const glm::vec3 &get_world_direction() const
        {
            return _world_direction;
        }

        float get_exponent() const
        {
            return _exponent;
        }

        void set_exponent(float exponent)
        {
            _exponent = exponent;
        }

        float get_cutoff_angle() const
        {
            return _cutoff_angle;
        }

        void set_cutoff_angle(float cutoff_angle)
        {
            _cutoff_angle = cutoff_angle;
        }

    private:
        float _attenuation_distance{10.0f};

        bool _use_constant_linear_quadratic_attenuation{false};
        float _constant_attenuation{1.0f};
        float _linear_attenuation{0.0f};
        float _quadratic_attenuation{0.0f};

        float _culling_range{100.0f};

        glm::vec3 _direction{0.0f, 1.0f, 0.0f};
        glm::vec3 _world_direction{0.0f, 1.0f, 0.0f};

        float _exponent{0.0f};
        float _cutoff_angle{0.79f};
    };
}

#endif
