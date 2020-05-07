#ifndef ES2_PHONG_MATERIAL_HPP
#define ES2_PHONG_MATERIAL_HPP

#include "materials/phong_material.hpp"

#include "utilities/utilities.hpp"
#include "renderer/es2_shader.hpp"

#include <GL/glew.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <string>
#include <vector>
#include <memory>

namespace aur
{
    class ES2PhongMaterial : public PhongMaterial
    {
    public:
        ES2PhongMaterial()
        {
            _vertex_shader_source = file_utilities::read_text_file("data/shaders/es2_phong_shader.vert");
            _fragment_shader_source = file_utilities::read_text_file("data/shaders/es2_phong_shader.frag");

            std::vector<std::string> attributes{
                "position",
                "color",
                "normal",
                "texture1_coordinates",
                "texture2_coordinates"
            };
            std::vector<std::string> uniforms{
                "model_view_matrix",
                "projection_matrix",
                "normal_matrix",
                "point_size",

                "ambient_light_color",

                "material_ambient_color",
                "material_diffuse_color",
                "material_emission_color",
                "material_specular_color",
                "material_specular_exponent",

                "directional_light_enabled[0]",
                "directional_light_two_sided[0]",
                "directional_light_view_direction[0]",
                "directional_light_ambient_color[0]",
                "directional_light_diffuse_color[0]",
                "directional_light_specular_color[0]",
                "directional_light_intensity[0]",

                "point_light_enabled[0]",
                "point_light_two_sided[0]",
                "point_light_view_position[0]",
                "point_light_ambient_color[0]",
                "point_light_diffuse_color[0]",
                "point_light_specular_color[0]",
                "point_light_intensity[0]",
                "point_light_constant_attenuation[0]",
                "point_light_linear_attenuation[0]",
                "point_light_quadratic_attenuation[0]",

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

            _shader = std::make_shared<ES2Shader>(_vertex_shader_source, _fragment_shader_source, attributes, uniforms);
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
                                    _convert_blending_func_to_es2_blending_func(_destination_color_blending_function),
                                    _convert_blending_func_to_es2_blending_func(_source_alpha_blending_function),
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
                glFrontFace(_convert_front_face_order_to_es2_front_face_order(_front_face_order));
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

            _update_light_uniforms_if_necessary(scene);
            if (_shader->is_dead()) { return; }

            auto camera = scene->get_camera();

            glm::mat4 model_view_matrix;
            if (is_overlay()) {
                model_view_matrix = mesh->get_world_matrix();
                model_view_matrix[3][2] = 0.0f;
            } else {
                model_view_matrix = camera->get_view_matrix() * mesh->get_world_matrix();
            }
            int model_view_matrix_uniform_location{_shader->get_uniforms().at("model_view_matrix")};
            glUniformMatrix4fv(
                model_view_matrix_uniform_location,
                1, GL_FALSE,
                glm::value_ptr(model_view_matrix)
            );

            glm::mat4 projection_matrix;
            if (is_overlay()) {
                projection_matrix = camera->get_orthographic_projection_matrix();
            } else {
                projection_matrix = camera->get_projection_matrix();
            }
            int projection_matrix_uniform_location{_shader->get_uniforms().at("projection_matrix")};
            glUniformMatrix4fv(
                projection_matrix_uniform_location,
                1, GL_FALSE,
                glm::value_ptr(projection_matrix)
            );

            glm::mat3 normal_matrix = glm::inverseTranspose(glm::mat3(model_view_matrix));
            int normal_matrix_uniform_location{_shader->get_uniforms().at("normal_matrix")};
            glUniformMatrix3fv(
                normal_matrix_uniform_location,
                1, GL_FALSE,
                glm::value_ptr(normal_matrix)
            );

            if (_point_sizing_enabled && !_prefer_point_size_from_geometry) {
                int point_size_uniform_location{_shader->get_uniforms().at("point_size")};
                glUniform1f(point_size_uniform_location, _point_size);
            }

            int ambient_light_color_uniform_location{_shader->get_uniforms().at("ambient_light_color")};
            glUniform3fv(
                ambient_light_color_uniform_location,
                1, glm::value_ptr(scene->get_ambient_light()->get_ambient_color())
            );

            int material_ambient_color_uniform_location{_shader->get_uniforms().at("material_ambient_color")};
            glUniform3fv(
                material_ambient_color_uniform_location,
                1, glm::value_ptr(_ambient_color)
            );

            int material_diffuse_color_uniform_location{_shader->get_uniforms().at("material_diffuse_color")};
            glUniform4fv(
                material_diffuse_color_uniform_location,
                1, glm::value_ptr(_diffuse_color)
            );

            int material_emission_color_uniform_location{_shader->get_uniforms().at("material_emission_color")};
            glUniform4fv(
                material_emission_color_uniform_location,
                1, glm::value_ptr(_emission_color)
            );

            int material_specular_color_uniform_location{_shader->get_uniforms().at("material_specular_color")};
            glUniform3fv(
                material_specular_color_uniform_location,
                1, glm::value_ptr(_specular_color)
            );

            int material_specular_exponent_uniform_location{_shader->get_uniforms().at("material_specular_exponent")};
            glUniform1f(material_specular_exponent_uniform_location, _specular_exponent);

            auto &directional_lights = scene->get_directional_lights();
            for (std::vector<std::shared_ptr<DirectionalLight>>::size_type i = 0; i < directional_lights.size(); ++i) {
                const auto &directional_light = directional_lights[i];

                int uniform_location = _shader->get_uniforms().at(_uniform_at_index("directional_light_enabled", i));
                glUniform1i(uniform_location, directional_light->is_enabled());

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("directional_light_two_sided", i));
                glUniform1i(uniform_location, directional_light->is_two_sided());

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("directional_light_view_direction", i));
                glUniform3fv(
                    uniform_location,
                    1, glm::value_ptr(camera->get_view_matrix() * glm::vec4(directional_light->get_world_direction(), 0.0f))
                );

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("directional_light_ambient_color", i));
                glUniform3fv(
                    uniform_location,
                    1, glm::value_ptr(directional_light->get_ambient_color())
                );

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("directional_light_diffuse_color", i));
                glUniform3fv(
                    uniform_location,
                    1, glm::value_ptr(directional_light->get_diffuse_color())
                );

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("directional_light_specular_color", i));
                glUniform3fv(
                    uniform_location,
                    1, glm::value_ptr(directional_light->get_specular_color())
                );

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("directional_light_intensity", i));
                glUniform1f(uniform_location, directional_light->get_intensity());
            }

            auto &point_lights = scene->get_point_lights();
            for (std::vector<std::shared_ptr<PointLight>>::size_type i = 0; i < point_lights.size(); ++i) {
                const auto &point_light = point_lights[i];

                int uniform_location = _shader->get_uniforms().at(_uniform_at_index("point_light_enabled", i));
                glUniform1i(uniform_location, point_light->is_enabled());

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("point_light_two_sided", i));
                glUniform1i(uniform_location, point_light->is_two_sided());

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("point_light_view_position", i));
                glUniform3fv(
                    uniform_location,
                    1, glm::value_ptr(camera->get_view_matrix() * point_light->get_world_matrix() * glm::vec4(point_light->get_position(), 1.0f))
                );

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("point_light_ambient_color", i));
                glUniform3fv(
                    uniform_location,
                    1, glm::value_ptr(point_light->get_ambient_color())
                );

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("point_light_diffuse_color", i));
                glUniform3fv(
                    uniform_location,
                    1, glm::value_ptr(point_light->get_diffuse_color())
                );

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("point_light_specular_color", i));
                glUniform3fv(
                    uniform_location,
                    1, glm::value_ptr(point_light->get_specular_color())
                );

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("point_light_intensity", i));
                glUniform1f(uniform_location, point_light->get_intensity());

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("point_light_constant_attenuation", i));
                glUniform1f(uniform_location, point_light->get_constant_attenuation());

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("point_light_linear_attenuation", i));
                glUniform1f(uniform_location, point_light->get_linear_attenuation());

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("point_light_quadratic_attenuation", i));
                glUniform1f(uniform_location, point_light->get_quadratic_attenuation());
            }

            auto &spot_lights = scene->get_spot_lights();
            for (std::vector<std::shared_ptr<SpotLight>>::size_type i = 0; i < spot_lights.size(); ++i) {
                const auto &spot_light = spot_lights[i];

                int uniform_location = _shader->get_uniforms().at(_uniform_at_index("spot_light_enabled", i));
                glUniform1i(uniform_location, spot_light->is_enabled());

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("spot_light_two_sided", i));
                glUniform1i(uniform_location, spot_light->is_two_sided());

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("spot_light_view_position", i));
                glUniform3fv(
                    uniform_location,
                    1, glm::value_ptr(camera->get_view_matrix() * spot_light->get_world_matrix() * glm::vec4(spot_light->get_position(), 1.0f))
                );

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("spot_light_view_direction", i));
                glUniform3fv(
                    uniform_location,
                    1, glm::value_ptr(camera->get_view_matrix() * glm::vec4(spot_light->get_world_direction(), 0.0f))
                );

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("spot_light_ambient_color", i));
                glUniform3fv(
                    uniform_location,
                    1, glm::value_ptr(spot_light->get_ambient_color())
                );

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("spot_light_diffuse_color", i));
                glUniform3fv(
                    uniform_location,
                    1, glm::value_ptr(spot_light->get_diffuse_color())
                );

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("spot_light_specular_color", i));
                glUniform3fv(
                    uniform_location,
                    1, glm::value_ptr(spot_light->get_specular_color())
                );

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("spot_light_exponent", i));
                glUniform1f(uniform_location, spot_light->get_exponent());

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("spot_light_cutoff_angle_cosine", i));
                glUniform1f(uniform_location, spot_light->get_cutoff_angle());

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("spot_light_intensity", i));
                glUniform1f(uniform_location, spot_light->get_intensity());

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("spot_light_constant_attenuation", i));
                glUniform1f(uniform_location, spot_light->get_constant_attenuation());

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("spot_light_linear_attenuation", i));
                glUniform1f(uniform_location, spot_light->get_linear_attenuation());

                uniform_location = _shader->get_uniforms().at(_uniform_at_index("spot_light_quadratic_attenuation", i));
                glUniform1f(uniform_location, spot_light->get_quadratic_attenuation());
            }

            if (_texture1) {
                _texture1->update(0);

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
                _texture2->update(1);

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
                _texture1->use(0);
            }
            if (_texture2) {
                _texture2->use(1);
            }
        }

    private:
        static std::string _uniform_at_index(const std::string &uniform, int slot)
        {
            return uniform + "[" + std::to_string(slot) + "]";
        }

        void _update_light_uniforms_if_necessary(const std::shared_ptr<Scene> &scene)
        {
            int directional_light_count = scene->get_directional_lights().size();
            int point_light_count = scene->get_point_lights().size();
            int spot_light_count = scene->get_spot_lights().size();

            if (_previous_directional_light_count != directional_light_count ||
                _previous_point_light_count != point_light_count ||
                _previous_spot_light_count != spot_light_count) {
                std::vector<std::string> uniforms{
                    "model_view_matrix",
                    "projection_matrix",
                    "normal_matrix",
                    "point_size",

                    "ambient_light_color",

                    "material_ambient_color",
                    "material_diffuse_color",
                    "material_emission_color",
                    "material_specular_color",
                    "material_specular_exponent",

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

                std::vector<std::string> directional_light_uniforms{
                    "directional_light_enabled",
                    "directional_light_two_sided",
                    "directional_light_view_direction",
                    "directional_light_ambient_color",
                    "directional_light_diffuse_color",
                    "directional_light_specular_color",
                    "directional_light_intensity"
                };

                std::vector<std::string> point_light_uniforms{
                    "point_light_enabled",
                    "point_light_two_sided",
                    "point_light_view_position",
                    "point_light_ambient_color",
                    "point_light_diffuse_color",
                    "point_light_specular_color",
                    "point_light_intensity",
                    "point_light_constant_attenuation",
                    "point_light_linear_attenuation",
                    "point_light_quadratic_attenuation"
                };

                std::vector<std::string> spot_light_uniforms{
                    "spot_light_enabled",
                    "spot_light_two_sided",
                    "spot_light_view_position",
                    "spot_light_view_direction",
                    "spot_light_ambient_color",
                    "spot_light_diffuse_color",
                    "spot_light_specular_color",
                    "spot_light_exponent",
                    "spot_light_cutoff_angle_cosine",
                    "spot_light_intensity",
                    "spot_light_constant_attenuation",
                    "spot_light_linear_attenuation",
                    "spot_light_quadratic_attenuation"
                };

                auto &uniform_map = _shader->get_uniforms();
                uniform_map.clear();

                for (const auto &uniform : uniforms) {
                    uniform_map[uniform] = -1;
                }
                for (const auto &uniform : directional_light_uniforms) {
                    for (int i = 0; i < directional_light_count; ++i) {
                        uniform_map[_uniform_at_index(uniform, i)] = -1;
                    }
                }
                for (const auto &uniform : point_light_uniforms) {
                    for (int i = 0; i < point_light_count; ++i) {
                        uniform_map[_uniform_at_index(uniform, i)] = -1;
                    }
                }
                for (const auto &uniform : spot_light_uniforms) {
                    for (int i = 0; i < spot_light_count; ++i) {
                        uniform_map[_uniform_at_index(uniform, i)] = -1;
                    }
                }

                _shader->set_fragment_shader_source(
                    "#define DIRECTIONAL_LIGHT_COUNT " + std::to_string(directional_light_count) + "\n" +
                    "#define POINT_LIGHT_COUNT " + std::to_string(point_light_count) + "\n" +
                    "#define SPOT_LIGHT_COUNT " + std::to_string(spot_light_count) + "\n\n" +
                    _fragment_shader_source
                );
                _shader->compile();

                _previous_directional_light_count = directional_light_count;
                _previous_point_light_count = point_light_count;
                _previous_spot_light_count = spot_light_count;
            }
        }

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

        std::string _vertex_shader_source;
        std::string _fragment_shader_source;

        int _previous_directional_light_count{1};
        int _previous_point_light_count{1};
        int _previous_spot_light_count{0};
    };
}

#endif
