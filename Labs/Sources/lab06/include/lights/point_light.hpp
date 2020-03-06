#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "lights/light.hpp"

namespace aur {
    class PointLight : public Light {
    public:
        float get_attenuation_distance() const {
            return _attenuation_distance;
        }

        void set_attenuation_distance(float attenuation_distance) {
            _attenuation_distance = attenuation_distance;
        }

        bool is_use_constant_linear_quadratic_attenuation() const {
            return _use_constant_linear_quadratic_attenuation;
        }

        void set_use_constant_linear_quadratic_attenuation(bool use_constant_linear_quadratic_attenuation) {
            _use_constant_linear_quadratic_attenuation = use_constant_linear_quadratic_attenuation;
        }

        float get_constant_attenuation() const {
            return _constant_attenuation;
        }

        void set_constant_attenuation(float constant_attenuation) {
            _constant_attenuation = constant_attenuation;
        }

        float get_linear_attenuation() const {
            return _linear_attenuation;
        }

        void set_linear_attenuation(float linear_attenuation) {
            _linear_attenuation = linear_attenuation;
        }

        float get_quadratic_attenuation() const {
            return _quadratic_attenuation;
        }

        void set_quadratic_attenuation(float quadratic_attenuation) {
            _quadratic_attenuation = quadratic_attenuation;
        }

        float get_culling_range() const {
            return _culling_range;
        }

        void set_culling_range(float culling_range) {
            _culling_range = culling_range;
        }

    private:
        float _attenuation_distance { 10.0f };

        bool _use_constant_linear_quadratic_attenuation { false };
        float _constant_attenuation { 1.0f };
        float _linear_attenuation { 0.0f };
        float _quadratic_attenuation { 0.0f };

        float _culling_range { 100.0f };
    };
}

#endif
