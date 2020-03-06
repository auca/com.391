#ifndef SCENE_HPP
#define SCENE_HPP

#include "objects/object.hpp"
#include "objects/camera.hpp"
#include "lights/ambient_light.hpp"
#include "lights/directional_light.hpp"
#include "lights/point_light.hpp"
#include "lights/spot_light.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <memory>
#include <utility>

namespace aur {
    class Scene {
    public:
        explicit Scene(const std::vector<std::shared_ptr<Object>> &objects)
            : _root{ std::make_shared<Object>() }, _camera { std::make_shared<Camera>() },
              _ambient_light { std::make_shared<AmbientLight>() },
              _directional_lights { { std::make_shared<DirectionalLight>() } },
              _point_lights { { std::make_shared<PointLight>() } } {
            for (const auto &object : objects) {
                _root->add_child(object);
            }
        }

        const glm::vec4 &get_clear_color() const {
            return _clear_color;
        }

        void set_clear_color(const glm::vec4 &clearColor) {
            _clear_color = clearColor;
        }

        const std::shared_ptr<Object> &get_root() const {
            return _root;
        }

        void set_root(const std::shared_ptr<Object> &root) {
            _root = root;
        }

        const std::shared_ptr<Camera> &get_camera() const {
            return _camera;
        }

        void set_camera(const std::shared_ptr<Camera> &camera) {
            _camera = camera;
        }

        const std::shared_ptr<AmbientLight> &get_ambient_light() const {
            return _ambient_light;
        }

        void set_ambient_light(const std::shared_ptr<AmbientLight> &ambient_light) {
            _ambient_light = ambient_light;
        }

        const std::vector<std::shared_ptr<DirectionalLight>> &get_directional_lights() const {
            return _directional_lights;
        }

        const std::vector<std::shared_ptr<PointLight>> &get_point_lights() const {
            return _point_lights;
        }

        const std::vector<std::shared_ptr<SpotLight>> &get_spot_lights() const {
            return _spot_lights;
        }

        std::vector<std::shared_ptr<DirectionalLight>> &get_directional_lights() {
            return _directional_lights;
        }

        std::vector<std::shared_ptr<PointLight>> &get_point_lights() {
            return _point_lights;
        }

        std::vector<std::shared_ptr<SpotLight>> &get_spot_lights() {
            return _spot_lights;
        }

    private:
        glm::vec4 _clear_color{ 0.0f };

        std::shared_ptr<Object> _root;
        std::shared_ptr<Camera> _camera;

        std::shared_ptr<AmbientLight> _ambient_light;
        std::vector<std::shared_ptr<DirectionalLight>> _directional_lights;
        std::vector<std::shared_ptr<PointLight>> _point_lights;
        std::vector<std::shared_ptr<SpotLight>> _spot_lights;
    };
}

#endif
