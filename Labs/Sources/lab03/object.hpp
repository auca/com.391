#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "geometry.hpp"
#include "material.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <utility>

class Object {
public:
    explicit Object(
        const glm::vec3 &position = glm::vec4(0.0f),
        const glm::vec3 &rotation = glm::vec4(0.0f),
        const glm::vec3 &scale = glm::vec4(1.0f)
    ) : _position { position }, _rotation { rotation }, _scale { scale } { }

    virtual ~Object() = default;

    glm::vec3 &get_position() {
        return _position;
    }

    void set_position(const glm::vec3 &position) {
        _position = position;
    }

    glm::vec3 &get_rotation() {
        return _rotation;
    }

    void set_rotation(const glm::vec3 &rotation) {
        _rotation = rotation;
    }

    glm::vec3 &get_scale() {
        return _scale;
    }

    void set_scale(const glm::vec3 &scale) {
        _scale = scale;
    }

    const glm::mat4 &get_model_matrix() const {
        return _model_matrix;
    }

    void update_model_matrix() {
        _model_matrix = glm::translate(glm::mat4(1.0f), _position);
        _model_matrix = glm::rotate(_model_matrix, _rotation.y, glm::vec3(0, 1, 0));
        _model_matrix = glm::rotate(_model_matrix, _rotation.x, glm::vec3(1, 0, 0));
        _model_matrix = glm::rotate(_model_matrix, _rotation.z, glm::vec3(0, 0, 1));
        _model_matrix = glm::scale(_model_matrix, _scale);
    }

protected:
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;

    glm::mat4 _model_matrix { 1.0f };
};

#endif
