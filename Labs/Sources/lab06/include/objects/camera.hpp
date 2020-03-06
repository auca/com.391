#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "objects/object.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace aur {
    class Camera : public Object {
    public:
        Camera() : Object{"camera"} {}

        bool should_receive_aspect_ratio_from_renderer() const {
            return _receive_aspect_ratio_from_renderer;
        }

        void set_receive_aspect_ratio_from_renderer(bool receive_aspect_ratio_from_renderer) {
            _receive_aspect_ratio_from_renderer = receive_aspect_ratio_from_renderer;
        }

        float get_aspect_ratio() const {
            return _aspect_ratio;
        }

        void set_aspect_ratio(float aspect_ratio) {
            if (_aspect_ratio != aspect_ratio) {
                _aspect_ratio = aspect_ratio;
                set_projection_matrix_requires_update(true);
            }
        }

        float get_field_of_view() const {
            return _field_of_view;
        }

        void set_field_of_view(float field_of_view) {
            if (_field_of_view != field_of_view) {
                _field_of_view = field_of_view;
                set_projection_matrix_requires_update(true);
            }
        }

        float get_near_plane() const {
            return _near_plane;
        }

        void set_near_plane(float near_plane) {
            if (_near_plane != near_plane) {
                _near_plane = near_plane;
                set_projection_matrix_requires_update(true);
            }
        }

        float get_far_plane() const {
            return _far_plane;
        }

        void set_far_plane(float far_plane) {
            if (_far_plane != far_plane) {
                _far_plane = far_plane;
                set_projection_matrix_requires_update(true);
            }
        }

        const glm::mat4 &get_view_matrix() {
            _update_view_matrix_if_necessary();

            return _view_matrix;
        }

        const glm::mat4 &get_projection_matrix() {
            _update_projection_matrix_if_necessary();

            return _projection_matrix;
        }

        const glm::mat4 &get_view_projection_matrix() {
            _update_view_projection_matrix_if_necessary();

            return _view_projection_matrix;
        }

        void set_model_matrix_requires_update(bool model_matrix_requires_update) final {
            Object::set_model_matrix_requires_update(model_matrix_requires_update);

            if (model_matrix_requires_update) {
                _view_matrix_requires_update = true;
                _view_projection_matrix_requires_update = true;
            }
        }

        void set_world_matrix_requires_update(bool world_matrix_requires_update) final {
            Object::set_world_matrix_requires_update(world_matrix_requires_update);

            if (world_matrix_requires_update) {
                _view_matrix_requires_update = true;
                _view_projection_matrix_requires_update = true;
            }
        }

        bool is_view_matrix_requires_update() const {
            return _view_matrix_requires_update;
        }

        void set_view_matrix_requires_update(bool view_matrix_requires_update) {
            _view_matrix_requires_update = view_matrix_requires_update;
            if (_view_matrix_requires_update) {
                _view_projection_matrix_requires_update = true;
            }
        }

        bool is_projection_matrix_requires_update() const {
            return _projection_matrix_requires_update;
        }

        void set_projection_matrix_requires_update(bool projection_matrix_requires_update) {
            _projection_matrix_requires_update = projection_matrix_requires_update;
            if (_projection_matrix_requires_update) {
                _view_projection_matrix_requires_update = true;
            }
        }

        bool is_view_projection_matrix_requires_update() const {
            return _view_projection_matrix_requires_update;
        }

        void set_view_projection_matrix_requires_update(bool view_projection_matrix_requires_update) {
            _view_projection_matrix_requires_update = view_projection_matrix_requires_update;
        }

    private:
        bool _receive_aspect_ratio_from_renderer{true};
        float _aspect_ratio{1.0f};
        float _field_of_view{1.13f};
        float _near_plane{0.01f};
        float _far_plane{1000.0f};

        bool _view_matrix_requires_update{true};
        glm::mat4 _view_matrix{1.0f};
        bool _projection_matrix_requires_update{true};
        glm::mat4 _projection_matrix{1.0f};
        bool _view_projection_matrix_requires_update{true};
        glm::mat4 _view_projection_matrix{1.0f};

        void _update_view_matrix_if_necessary() {
            if (_view_matrix_requires_update) {
                _update_world_matrix_if_necessary();

                _view_matrix = glm::inverse(_world_matrix);
                _view_matrix_requires_update = false;
            }
        }

        void _update_projection_matrix_if_necessary() {
            if (_projection_matrix_requires_update) {
                _projection_matrix = glm::perspective<float>(
                    _field_of_view,
                    _aspect_ratio,
                    _near_plane,
                    _far_plane
                );
                _projection_matrix_requires_update = false;
            }
        }

        void _update_view_projection_matrix_if_necessary() {
            if (_view_projection_matrix_requires_update) {
                _update_view_matrix_if_necessary();
                _update_projection_matrix_if_necessary();

                _view_projection_matrix = _projection_matrix * _view_matrix;
                _view_projection_matrix_requires_update = false;
            }
        }
    };
}

#endif
