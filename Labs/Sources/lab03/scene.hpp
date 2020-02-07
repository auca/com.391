#ifndef SCENE_HPP
#define SCENE_HPP

#include "object.hpp"
#include "camera.hpp"

#include <vector>
#include <memory>
#include <utility>

class Scene {
public:
    explicit Scene(const std::vector<Object *> &objects = { }) {
        for (auto object : objects) {
            _objects.push_back(std::shared_ptr<Object>(object));
        }
    }

    const glm::vec4 &get_clear_color() const {
        return _clear_color;
    }

    void set_clear_color(const glm::vec4 &clearColor) {
        _clear_color = clearColor;
    }

    const std::vector<std::shared_ptr<Object>> & get_objects() const {
        return _objects;
    }

    void set_objects(const std::vector<std::shared_ptr<Object>> &objects) {
        _objects = objects;
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
    glm::vec4 _clear_color { 0.0f };

    std::vector<std::shared_ptr<Object>> _objects;

    Camera _camera;
};

#endif
