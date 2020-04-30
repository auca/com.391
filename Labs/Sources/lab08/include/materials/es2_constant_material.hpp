#ifndef ES2_CONSTANT_MATERIAL_HPP
#define ES2_CONSTANT_MATERIAL_HPP

#include "materials/constant_material.hpp"

#include "utilities/utilities.hpp"
#include "renderer/es2_shader.hpp"

#include <GL/glew.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>
#include <memory>

namespace aur
{
    class ES2ConstantMaterial : public ConstantMaterial
    {
    public:
        ES2ConstantMaterial()
        {
            std::string vertex_shader_source{file_utilities::read_text_file("data/shaders/es2_constant_shader.vert")};
            std::string fragment_shader_source{file_utilities::read_text_file("data/shaders/es2_constant_shader.frag")};
            std::vector<std::string> attributes{
                "position",
                "color",
                "texture1_coordinates",
                "texture2_coordinates"
            };
            std::vector<std::string> uniforms{
                "model_view_matrix",
                "projection_matrix",
                "emission_color",
                "point_size",

                "texture1_sampler",
                "texture1_enabled",
                "texture1_transformation_enabled",
                "texture1_transformation_matrix",
                "texturing_mode1",

                "texture2_sampler",
                "texture2_enabled",
                "texture2_transformation_enabled",
                "texture2_transformation_matrix",
                "texturing_mode2",

                "fog_enabled",
                "fog_type",
                "fog_depth",
                "fog_color",
                "fog_far_minus_near_plane",
                "fog_far_plane",
                "fog_density"
            };

            _shader = std::make_shared<ES2Shader>(vertex_shader_source, fragment_shader_source, attributes, uniforms);
        }

        void update(std::shared_ptr<Scene> scene, std::shared_ptr<Mesh> mesh) final
        {
            if (_shader->is_dead()) {
                return;
            } else if (!_shader->is_compiled()) {
                _shader->compile();
                if (_shader->is_dead()) { return; }
            }

            if (!_prefer_line_width_from_geometry) {
                glLineWidth(static_cast<GLfloat>(_line_width));
            }

            glDepthMask(static_cast<GLboolean>(_depth_mask_enabled));
            if (_depth_test_enabled) {
                glEnable(GL_DEPTH_TEST);
            } else {
                glDisable(GL_DEPTH_TEST);
            }
            if (_depth_test_enabled) {
                glDepthFunc(_convert_depth_test_func_to_es2_depth_test_func(_depth_test_function));
            }

            if (_blending_enabled) {
                glEnable(GL_BLEND);
            } else {
                glDisable(GL_BLEND);
            }
            if (_blending_enabled) {
                glBlendEquationSeparate(_convert_blending_equation_to_es2_blending_equation(_color_blending_equation),
                                        _convert_blending_equation_to_es2_blending_equation(_alpha_blending_equation));
                glBlendFuncSeparate(_convert_blending_func_to_es2_blending_func(_source_color_blending_function),
                                    _convert_blending_func_to_es2_blending_func(_source_alpha_blending_function),
                                    _convert_blending_func_to_es2_blending_func(_destination_color_blending_function),
                                    _convert_blending_func_to_es2_blending_func(_destination_alpha_blending_function));
                glBlendColor(static_cast<GLclampf>(_blending_constant_color[0]),
                             static_cast<GLclampf>(_blending_constant_color[1]),
                             static_cast<GLclampf>(_blending_constant_color[2]),
                             static_cast<GLclampf>(_blending_constant_color[3]));
            }

            if (_face_culling_enabled) {
                glEnable(GL_CULL_FACE);
            } else {
                glDisable(GL_CULL_FACE);
            }
            if (_face_culling_enabled) {
                glCullFace(_convert_cull_face_mode_to_es2_cull_face_mode(_cull_face_mode));
                glCullFace(_convert_front_face_order_to_es2_front_face_order(_front_face_order));
            }

            if (_polygon_offset_enabled) {
                glEnable(GL_POLYGON_OFFSET_FILL);
            } else {
                glDisable(GL_POLYGON_OFFSET_FILL);
            }
            if (_polygon_offset_enabled) {
                glPolygonOffset(static_cast<GLfloat>(_polygon_offset_factor),
                                static_cast<GLfloat>(_polygon_offset_units));
            }

            auto camera = scene->get_camera();

            glm::mat4 model_view_matrix = camera->get_view_matrix() * mesh->get_world_matrix();
            int model_view_matrix_uniform_location{_shader->get_uniforms().at("model_view_matrix")};
            glUniformMatrix4fv(
                model_view_matrix_uniform_location,
                1, GL_FALSE,
                glm::value_ptr(model_view_matrix)
            );

            glm::mat4 projection_matrix = camera->get_projection_matrix();
            int projection_matrix_uniform_location{_shader->get_uniforms().at("projection_matrix")};
            glUniformMatrix4fv(
                projection_matrix_uniform_location,
                1, GL_FALSE,
                glm::value_ptr(projection_matrix)
            );

            if (_point_sizing_enabled && !_prefer_point_size_from_geometry) {
                int point_size_uniform_location{_shader->get_uniforms().at("point_size")};
                glUniform1f(point_size_uniform_location, _point_size);
            }

            int emission_color_uniform_location{_shader->get_uniforms().at("emission_color")};
            glUniform4fv(
                emission_color_uniform_location,
                1, glm::value_ptr(_emission_color)
            );

            if (_texture1) {
                int texture1_enabled_uniform_location{_shader->get_uniforms().at("texture1_enabled")};
                glUniform1i(
                    texture1_enabled_uniform_location,
                    (GLint) _texture1->is_enabled()
                );

                if (_texture1->is_enabled()) {
                    int texture1_sampler_uniform_location{_shader->get_uniforms().at("texture1_sampler")};
                    glUniform1i(texture1_sampler_uniform_location, 0);

                    int texturing_mode1_uniform_location{_shader->get_uniforms().at("texturing_mode1")};
                    glUniform1i(
                        texturing_mode1_uniform_location,
                        (GLint) _texture1->get_mode()
                    );

                    int texture1_transformation_enabled_uniform_location{_shader->get_uniforms().at("texture1_transformation_enabled")};
                    glUniform1i(
                        texture1_transformation_enabled_uniform_location,
                        (GLint) _texture1->is_transformation_enabled()
                    );

                    int texture1_transformation_matrix_uniform_location{_shader->get_uniforms().at("texture1_transformation_matrix")};
                    glUniformMatrix4fv(
                        texture1_transformation_matrix_uniform_location,
                        1, GL_FALSE,
                        glm::value_ptr(_texture1->get_transformation_matrix())
                    );
                }
            }

            if (_texture2) {
                int texture2_enabled_uniform_location{_shader->get_uniforms().at("texture2_enabled")};
                glUniform1i(
                    texture2_enabled_uniform_location,
                    (GLint) _texture2->is_enabled()
                );

                if (_texture2->is_enabled()) {
                    int texture2_sampler_uniform_location{_shader->get_uniforms().at("texture2_sampler")};
                    glUniform1i(texture2_sampler_uniform_location, 1);

                    int texturing_mode2_uniform_location{_shader->get_uniforms().at("texturing_mode2")};
                    glUniform1i(
                        texturing_mode2_uniform_location,
                        (GLint) _texture2->get_mode()
                    );

                    int texture2_transformation_enabled_uniform_location{_shader->get_uniforms().at("texture2_transformation_enabled")};
                    glUniform1i(
                        texture2_transformation_enabled_uniform_location,
                        (GLint) _texture2->is_transformation_enabled()
                    );

                    int texture2_transformation_matrix_uniform_location{_shader->get_uniforms().at("texture2_transformation_matrix")};
                    glUniformMatrix4fv(
                        texture2_transformation_matrix_uniform_location,
                        1, GL_FALSE,
                        glm::value_ptr(_texture2->get_transformation_matrix())
                    );
                }
            }

            int fog_enabled_uniform_location{_shader->get_uniforms().at("fog_enabled")};
            glUniform1i(fog_enabled_uniform_location, (GLint) _fog_enabled);

            int fog_type_uniform_location{_shader->get_uniforms().at("fog_type")};
            glUniform1i(fog_type_uniform_location, (GLint) _fog_type);

            int fog_depth_uniform_location{_shader->get_uniforms().at("fog_depth")};
            glUniform1i(fog_depth_uniform_location, (GLint) _fog_depth);

            int fog_color_uniform_location{_shader->get_uniforms().at("fog_color")};
            glUniform3fv(
                fog_color_uniform_location,
                1, glm::value_ptr(_fog_color)
            );

            int fog_far_minus_near_plane_uniform_location{_shader->get_uniforms().at("fog_far_minus_near_plane")};
            glUniform1f(fog_far_minus_near_plane_uniform_location, _fog_far_plane - _fog_near_plane);

            int fog_far_plane_uniform_location{_shader->get_uniforms().at("fog_far_plane")};
            glUniform1f(fog_far_plane_uniform_location, _fog_far_plane);

            int fog_density_uniform_location{_shader->get_uniforms().at("fog_density")};
            glUniform1f(fog_density_uniform_location, _fog_density);
        }

        void use() final
        {
            _shader->use();
            if (_texture1) {
                _texture1->update(0);
                _texture1->use(0);
            }
            if (_texture2) {
                _texture2->update(1);
                _texture2->use(1);
            }
        }

    private:
        static GLenum _convert_depth_test_func_to_es2_depth_test_func(Material::DepthTestFunction depth_test_function)
        {
            switch (depth_test_function) {
                case Material::DepthTestFunction::Never:
                    return GL_NEVER;
                case Material::DepthTestFunction::Always:
                    return GL_ALWAYS;
                case Material::DepthTestFunction::Less:
                    return GL_LESS;
                case Material::DepthTestFunction::LowerOrEqual:
                    return GL_LEQUAL;
                case Material::DepthTestFunction::Equal:
                    return GL_EQUAL;
                case Material::DepthTestFunction::Greater:
                    return GL_GREATER;
                case Material::DepthTestFunction::GreaterOrEqual:
                    return GL_GEQUAL;
                case Material::DepthTestFunction::NotEqual:
                    return GL_NOTEQUAL;
                default:
                    return GL_LESS;
            }
        }

        static GLenum _convert_blending_equation_to_es2_blending_equation(Material::BlendingEquation blending_equation)
        {
            switch (blending_equation) {
                case Material::BlendingEquation::Addition:
                    return GL_FUNC_ADD;
                case Material::BlendingEquation::Subtraction:
                    return GL_FUNC_SUBTRACT;
                case Material::BlendingEquation::ReverseSubtraction:
                    return GL_FUNC_REVERSE_SUBTRACT;
                default:
                    return GL_FUNC_ADD;
            }
        }

        static GLenum _convert_blending_func_to_es2_blending_func(Material::BlendingFunction blending_function)
        {
            switch (blending_function) {
                case Zero:
                    return GL_ZERO;
                case One:
                    return GL_ONE;
                case SourceColor:
                    return GL_SRC_COLOR;
                case OneMinusSourceColor:
                    return GL_ONE_MINUS_SRC_COLOR;
                case DestinationColor:
                    return GL_DST_COLOR;
                case OneMinusDestinationColor:
                    return GL_ONE_MINUS_DST_COLOR;
                case SourceAlpha:
                    return GL_SRC_ALPHA;
                case OneMinusSourceAlpha:
                    return GL_ONE_MINUS_SRC_ALPHA;
                case DestinationAlpha:
                    return GL_DST_ALPHA;
                case OneMinusDestinationAlpha:
                    return GL_ONE_MINUS_DST_ALPHA;
                case ConstantColor:
                    return GL_CONSTANT_COLOR;
                case OneMinusConstantColor:
                    return GL_ONE_MINUS_CONSTANT_COLOR;
                case ConstantAlpha:
                    return GL_CONSTANT_ALPHA;
                case OneMinusConstantAlpha:
                    return GL_ONE_MINUS_CONSTANT_ALPHA;
                case SourceAlphaSaturate:
                    return GL_SRC_ALPHA_SATURATE;
                default:
                    return GL_SRC_ALPHA;
            }
        }

        static GLenum _convert_cull_face_mode_to_es2_cull_face_mode(Material::CullFaceMode cull_face_mode)
        {
            switch (cull_face_mode) {
                case Material::CullFaceMode::CullFrontFaces:
                    return GL_FRONT;
                case Material::CullFaceMode::CullBackFaces:
                    return GL_BACK;
                case Material::CullFaceMode::CullFrontAndBackFaces:
                    return GL_FRONT_AND_BACK;
                default:
                    return GL_BACK;
            }
        }

        static GLenum _convert_front_face_order_to_es2_front_face_order(Material::FrontFaceOrder front_face_order)
        {
            switch (front_face_order) {
                case Material::FrontFaceOrder::Clockwise:
                    return GL_CW;
                case Material::FrontFaceOrder::Counterclockwise:
                    return GL_CCW;
                default:
                    return GL_CW;
            }
        }
    };
}

#endif
