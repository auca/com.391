#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "object.hpp"

class Camera : public Object {
public:
    float get_aspect_ratio() const {
        return _aspect_ratio;
    }

    void set_aspect_ratio(float aspect_ratio) {
        _aspect_ratio = aspect_ratio;
    }

    float get_field_of_view() const {
        return _field_of_view;
    }

    void set_field_of_view(float field_of_view) {
        _field_of_view = field_of_view;
    }

    float get_near_plane() const {
        return _near_plane;
    }

    void set_near_plane(float near_plane) {
        _near_plane = near_plane;
    }

    float get_far_plane() const {
        return _far_plane;
    }

    void set_far_plane(float far_plane) {
        _far_plane = far_plane;
    }

    const glm::mat4 &get_view_matrix() const {
        return _view_matrix;
    }

    const glm::mat4 &get_projection_matrix() const {
        return _projection_matrix;
    }

    const glm::mat4 &get_view_projection_matrix() const {
        return _view_projection_matrix;
    }

    void update_view_matrix() {
        _view_matrix = glm::inverse(_model_matrix);
    }

    void update_projection_matrix() {
        _projection_matrix = glm::perspective<float>(
            _field_of_view,
            _aspect_ratio,
            _near_plane,
            _far_plane
        );
    }

    void update_view_projection_matrix() {
        _view_projection_matrix = _projection_matrix * _view_matrix;
    }

private:
    float _aspect_ratio { 1.0f };
    float _field_of_view { 1.0f };
    float _near_plane { 0.01f };
    float _far_plane { 1000.0f };

    glm::mat4 _view_matrix { 1.0f };
    glm::mat4 _projection_matrix { 1.0f };
    glm::mat4 _view_projection_matrix { 1.0f };
};

#endif
