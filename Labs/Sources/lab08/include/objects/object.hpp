#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <memory>
#include <utility>
#include <cmath>
#include <vector>

namespace aur
{
    class Object : public std::enable_shared_from_this<Object>
    {
    public:
        explicit Object(
            std::string name = "",
            const glm::vec3 &position = glm::vec4(0.0f),
            const glm::vec3 &rotation = glm::vec4(0.0f),
            const glm::vec3 &scale = glm::vec4(1.0f),
            std::weak_ptr<Object> parent = {})
            : _name{std::move(name)},
              _position{position}, _rotation{rotation}, _scale{scale},
              _world_position(position), _world_rotation(rotation), _world_scale(scale),
              _parent{std::move(parent)}
        {
            _update_quaternion_from_rotation();
        }

        virtual ~Object() = default;

        const std::string &get_name() const
        {
            return _name;
        }

        void set_name(const std::string &name)
        {
            _name = name;
        }

        const std::weak_ptr<Object> &get_parent() const
        {
            return _parent;
        }

        void set_parent(const std::weak_ptr<Object> &parent)
        {
            if (_parent.lock() != parent.lock()) {
                _parent = parent;
                set_world_matrix_requires_update(true);
            }
        }

        void add_child(const std::shared_ptr<Object> &child)
        {
            child->set_parent(shared_from_this());
            _children.push_back(child);
        }

        std::shared_ptr<Object> get_child(std::vector<std::shared_ptr<Object>>::size_type position) const
        {
            return _children[position];
        }

        void remove_child(std::vector<std::shared_ptr<Object>>::size_type position)
        {
            _children.erase(_children.begin() + position);
        }

        const std::vector<std::shared_ptr<Object>> &get_children() const
        {
            return _children;
        }

        glm::vec3 &get_position()
        {
            return _position;
        }

        void set_position(const glm::vec3 &position)
        {
            if (_position != position) {
                _position = position;
                set_model_matrix_requires_update(true);
            }
        }

        void add_to_position(const glm::vec3 &position)
        {
            if (position != glm::vec3(0.0f)) {
                _position += position;
                set_model_matrix_requires_update(true);
            }
        }

        glm::vec3 &get_rotation()
        {
            return _rotation;
        }

        void set_rotation(const glm::vec3 &rotation)
        {
            if (_rotation != rotation) {
                _rotation = rotation;
                _update_quaternion_from_rotation();
                set_model_matrix_requires_update(true);
            }
        }

        void add_to_rotation(const glm::vec3 &rotation)
        {
            if (rotation != glm::vec3(0.0f)) {
                _rotation += rotation;
                _update_quaternion_from_rotation();
                set_model_matrix_requires_update(true);
            }
        }

        glm::vec3 &get_scale()
        {
            return _scale;
        }

        void set_scale(const glm::vec3 &scale)
        {
            if (_scale != scale) {
                _scale = scale;
                set_model_matrix_requires_update(true);
            }
        }

        void add_to_scale(const glm::vec3 &scale)
        {
            if (scale != glm::vec3(0.0f)) {
                _scale += scale;
                set_model_matrix_requires_update(true);
            }
        }

        const glm::quat &get_quaternion_rotation() const
        {
            return _quaternion_rotation;
        }

        void set_quaternion_rotation(const glm::quat &quaternion_rotation)
        {
            if (_quaternion_rotation != quaternion_rotation) {
                _quaternion_rotation = quaternion_rotation;
                _update_rotation_from_quaternion();
                set_model_matrix_requires_update(true);
            }
        }

        float get_x() const
        {
            return _position.x;
        }

        void set_x(float x)
        {
            if (_position.x != x) {
                _position.x = x;
                set_model_matrix_requires_update(true);
            }
        }

        void add_to_x(float x)
        {
            if (x != 0.0f) {
                _position.x += x;
                set_model_matrix_requires_update(true);
            }
        }

        float get_y() const
        {
            return _position.y;
        }

        void set_y(float y)
        {
            if (_position.y != y) {
                _position.y = y;
                set_model_matrix_requires_update(true);
            }
        }

        void add_to_y(float y)
        {
            if (y != 0.0f) {
                _position.y += y;
                set_model_matrix_requires_update(true);
            }
        }

        float get_z() const
        {
            return _position.z;
        }

        void set_z(float z)
        {
            if (_position.z != z) {
                _position.z = z;
                set_model_matrix_requires_update(true);
            }
        }

        void add_to_z(float z)
        {
            if (z != 0.0f) {
                _position.z += z;
                set_model_matrix_requires_update(true);
            }
        }

        float get_rotation_x() const
        {
            return _rotation.x;
        }

        void set_rotation_x(float rotation_x)
        {
            if (_rotation.x != rotation_x) {
                _rotation.x = rotation_x;
                _update_quaternion_from_rotation();
                set_model_matrix_requires_update(true);
            }
        }

        void add_to_rotation_x(float rotation_x)
        {
            if (rotation_x != 0.0f) {
                _rotation.x += rotation_x;
                _update_quaternion_from_rotation();
                set_model_matrix_requires_update(true);
            }
        }

        float get_rotation_y() const
        {
            return _rotation.y;
        }

        void set_rotation_y(float rotation_y)
        {
            if (_rotation.y != rotation_y) {
                _rotation.y = rotation_y;
                _update_quaternion_from_rotation();
                set_model_matrix_requires_update(true);
            }
        }

        void add_to_rotation_y(float rotation_y)
        {
            if (rotation_y != 0.0f) {
                _rotation.y += rotation_y;
                _update_quaternion_from_rotation();
                set_model_matrix_requires_update(true);
            }
        }

        float get_rotation_z() const
        {
            return _rotation.z;
        }

        void set_rotation_z(float rotation_z)
        {
            if (_rotation.z != rotation_z) {
                _rotation.z = rotation_z;
                _update_quaternion_from_rotation();
                set_model_matrix_requires_update(true);
            }
        }

        void add_to_rotation_z(float rotation_z)
        {
            if (rotation_z != 0.0f) {
                _rotation.z += rotation_z;
                _update_quaternion_from_rotation();
                set_model_matrix_requires_update(true);
            }
        }

        float get_scale_x() const
        {
            return _scale.x;
        }

        void set_scale_x(float scale_x)
        {
            if (_scale.x != scale_x) {
                _scale.x = scale_x;
                set_model_matrix_requires_update(true);
            }
        }

        void add_to_scale_x(float scale_x)
        {
            if (scale_x != 0.0f) {
                _scale.x += scale_x;
                set_model_matrix_requires_update(true);
            }
        }

        float get_scale_y() const
        {
            return _scale.y;
        }

        void set_scale_y(float scale_y)
        {
            if (_scale.y != scale_y) {
                _scale.y = scale_y;
                set_model_matrix_requires_update(true);
            }
        }

        void add_to_scale_y(float scale_y)
        {
            if (scale_y != 0.0f) {
                _scale.y += scale_y;
                set_model_matrix_requires_update(true);
            }
        }

        float get_scale_z() const
        {
            return _scale.z;
        }

        void set_scale_z(float scale_z)
        {
            if (_scale.z != scale_z) {
                _scale.z = scale_z;
                set_model_matrix_requires_update(true);
            }
        }

        void add_to_scale_z(float scale_z)
        {
            if (scale_z != 0.0f) {
                _scale.z += scale_z;
                set_model_matrix_requires_update(true);
            }
        }

        const glm::vec3 &get_world_position()
        {
            _update_world_matrix_if_necessary();
            return _world_position;
        }

        const glm::vec3 &get_world_rotation()
        {
            _update_world_matrix_if_necessary();
            return _world_rotation;
        }

        const glm::vec3 &get_world_scale()
        {
            _update_world_matrix_if_necessary();
            return _world_scale;
        }

        const glm::quat &get_world_quaternion_rotation()
        {
            _update_world_matrix_if_necessary();
            return _world_quaternion_rotation;
        }

        const glm::vec3 &get_up() const
        {
            return _up;
        }

        void set_up(const glm::vec3 &up)
        {
            _up = up;
        }

        void look_at(const glm::vec3 &position) {
            look_at(position, _up);
        }

        void look_at(const glm::vec3 &position, const glm::vec3 &up) {
            glm::mat4 look_at_matrix = glm::lookAt(this->get_world_position(), position, up);
            glm::quat target_world_quaternion_rotation{look_at_matrix};

            if (const auto parent = _parent.lock()) {
                glm::quat parent_world_quaternion_rotation_inverse = glm::inverse(parent->get_world_quaternion_rotation());
                glm::quat quaternion_rotation = parent_world_quaternion_rotation_inverse * target_world_quaternion_rotation;
                set_quaternion_rotation(quaternion_rotation);
            } else {
                set_quaternion_rotation(target_world_quaternion_rotation);
            }
        }

        void look_at(const std::shared_ptr<Object> &target) {
            look_at(target->get_world_position(), _up);
        }

        const glm::mat4 &get_model_matrix()
        {
            _update_model_matrix_if_necessary();

            return _model_matrix;
        }

        const glm::mat4 &get_world_matrix()
        {
            _update_world_matrix_if_necessary();

            return _world_matrix;
        }

        bool is_model_matrix_requires_update() const
        {
            return _model_matrix_requires_update;
        }

        virtual void set_model_matrix_requires_update(bool model_matrix_requires_update)
        {
            _model_matrix_requires_update = model_matrix_requires_update;
            if (_model_matrix_requires_update) {
                _world_matrix_requires_update = true;

                for (const auto &child : _children) {
                    child->set_model_matrix_requires_update(true);
                    child->set_world_matrix_requires_update(true);
                }
            }
        }

        bool is_world_matrix_requires_update() const
        {
            return _world_matrix_requires_update;
        }

        virtual void set_world_matrix_requires_update(bool world_matrix_requires_update)
        {
            _world_matrix_requires_update = world_matrix_requires_update;
            if (_world_matrix_requires_update) {
                for (const auto &child : _children) {
                    child->set_world_matrix_requires_update(true);
                }
            }
        }

        bool is_billboard() const
        {
            return _billboard;
        }

        void set_billboard(bool billboard)
        {
            _billboard = billboard;
        }

    protected:
        std::string _name;

        glm::vec3 _position;
        glm::vec3 _rotation;
        glm::vec3 _scale;
        glm::quat _quaternion_rotation;

        glm::vec3 _world_position;
        glm::vec3 _world_rotation;
        glm::vec3 _world_scale;
        glm::quat _world_quaternion_rotation;

        glm::vec3 _up{0.0f, 1.0f, 0.0f};

        std::weak_ptr<Object> _parent;
        std::vector<std::shared_ptr<Object>> _children;

        bool _model_matrix_requires_update{true};
        glm::mat4 _model_matrix{1.0f};
        bool _world_matrix_requires_update{true};
        glm::mat4 _world_matrix{1.0f};
        bool _billboard{false};

        void _update_model_matrix_if_necessary()
        {
            if (_model_matrix_requires_update) {
                _model_matrix = glm::translate(glm::mat4(1.0f), _position);
                _model_matrix = glm::rotate(_model_matrix, _rotation.y, glm::vec3(0, 1, 0));
                _model_matrix = glm::rotate(_model_matrix, _rotation.x, glm::vec3(1, 0, 0));
                _model_matrix = glm::rotate(_model_matrix, _rotation.z, glm::vec3(0, 0, 1));
                _model_matrix = glm::scale(_model_matrix, _scale);
                _model_matrix_requires_update = false;
            }
        }

        void _update_world_matrix_if_necessary()
        {
            if (_world_matrix_requires_update) {
                _update_model_matrix_if_necessary();

                if (const auto parent = _parent.lock()) {
                    _world_matrix = parent->get_world_matrix() * _model_matrix;
                } else {
                    _world_matrix = _model_matrix;
                }
                _world_matrix_requires_update = false;

                /* Position */

                _world_position =
                    glm::vec3(
                        _world_matrix[3][0],
                        _world_matrix[3][1],
                        _world_matrix[3][2]
                    );

                /* Scale */

                _world_scale.x =
                    _world_matrix[0][0] * _world_matrix[0][0] +
                    _world_matrix[0][1] * _world_matrix[0][1] +
                    _world_matrix[0][2] * _world_matrix[0][2];

                _world_scale.y =
                    _world_matrix[1][0] * _world_matrix[1][0] +
                    _world_matrix[1][1] * _world_matrix[1][1] +
                    _world_matrix[1][2] * _world_matrix[1][2];

                _world_scale.z =
                    _world_matrix[2][0] * _world_matrix[2][0] +
                    _world_matrix[2][1] * _world_matrix[2][1] +
                    _world_matrix[2][2] * _world_matrix[2][2];

                _world_scale.x = sqrtf(_world_scale.x);
                _world_scale.y = sqrtf(_world_scale.y);
                _world_scale.z = sqrtf(_world_scale.z);

                /* Rotation */

                _world_quaternion_rotation = glm::quat(_world_matrix);

                float sqx = _world_quaternion_rotation[0] * _world_quaternion_rotation[0];
                float sqy = _world_quaternion_rotation[1] * _world_quaternion_rotation[1];
                float sqz = _world_quaternion_rotation[2] * _world_quaternion_rotation[2];
                float sqw = _world_quaternion_rotation[3] * _world_quaternion_rotation[3];

                _world_rotation.x =
                    atan2f(
                        2.0f * (_world_quaternion_rotation[0] * _world_quaternion_rotation[3] -
                                _world_quaternion_rotation[1] * _world_quaternion_rotation[2]),
                        sqw - sqx - sqy + sqz
                    );
                _world_rotation.y =
                    asinf(
                        fminf(fmaxf((
                            2.0f * (_world_quaternion_rotation[0] * _world_quaternion_rotation[2] +
                                    _world_quaternion_rotation[1] * _world_quaternion_rotation[3])
                        ), 0.0f), 1.0f)
                    );
                _world_rotation.z =
                    atan2f(
                        2.0f * (_world_quaternion_rotation[2] * _world_quaternion_rotation[3] -
                                _world_quaternion_rotation[0] * _world_quaternion_rotation[1]),
                        sqw + sqx - sqy - sqz
                    );
            }
        }

        void _update_quaternion_from_rotation()
        {
            float c1 = cosf(_rotation.x * 0.5f);
            float c2 = cosf(_rotation.y * 0.5f);
            float c3 = cosf(_rotation.z * 0.5f);
            float s1 = sinf(_rotation.x * 0.5f);
            float s2 = sinf(_rotation.y * 0.5f);
            float s3 = sinf(_rotation.z * 0.5f);

            _quaternion_rotation = glm::quat{
                s1 * c2 * c3 + c1 * s2 * s3,
                c1 * s2 * c3 - s1 * c2 * s3,
                c1 * c2 * s3 + s1 * s2 * c3,
                c1 * c2 * c3 - s1 * s2 * s3
            };
            _world_quaternion_rotation = _quaternion_rotation;
        }

        void _update_rotation_from_quaternion()
        {
            glm::quat normalized_quaternion = glm::normalize(_quaternion_rotation);

            float sqx = normalized_quaternion[0] * normalized_quaternion[0];
            float sqy = normalized_quaternion[1] * normalized_quaternion[1];
            float sqz = normalized_quaternion[2] * normalized_quaternion[2];
            float sqw = normalized_quaternion[3] * normalized_quaternion[3];

            _rotation.x =
                atan2f(
                    2.0f * (normalized_quaternion[0] * normalized_quaternion[3] -
                            normalized_quaternion[1] * normalized_quaternion[2]),
                    sqw - sqx - sqy + sqz
                );
            _rotation.y =
                asinf(
                    fminf(fmaxf((
                        2.0f * (normalized_quaternion[0] * normalized_quaternion[2] +
                                normalized_quaternion[1] * normalized_quaternion[3])
                    ), 0.0f), 1.0f)
                );
            _rotation.z =
                atan2f(
                    2.0f * (normalized_quaternion[2] * normalized_quaternion[3] -
                            normalized_quaternion[0] * normalized_quaternion[1]),
                    sqw + sqx - sqy - sqz
                );

            _quaternion_rotation = normalized_quaternion;
        }
    };
}

#endif
