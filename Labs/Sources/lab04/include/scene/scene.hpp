#ifndef SCENE_HPP
#define SCENE_HPP

#include "objects/object.hpp"
#include "objects/camera.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <memory>
#include <utility>

namespace aur {
    class Scene {
    public:
        explicit Scene(const std::vector<std::shared_ptr<Object>> &objects)
            : _root{std::make_shared<Object>()} {
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

        const Camera &get_camera() const {
            return _camera;
        }

        Camera &get_camera() {
            return _camera;
        }

        void set_camera(const Camera &camera) {
            _camera = camera;
        }

    private:
        glm::vec4 _clear_color{ 0.0f };

        std::shared_ptr<Object> _root;
        Camera _camera;
    };
}

#endif
