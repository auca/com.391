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
                "texturing_mode2"
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

            _update_light_uniforms_if_necessary(scene);
            if (_shader->is_dead()) { return; }

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

            glm::mat3 normal_matrix = glm::inverseTranspose(glm::mat3(model_view_matrix));
            int normal_matrix_uniform_location{_shader->get_uniforms().at("normal_matrix")};
            glUniformMatrix3fv(
                normal_matrix_uniform_location,
                1, GL_FALSE,
                glm::value_ptr(normal_matrix)
            );

            int point_size_uniform_location{_shader->get_uniforms().at("point_size")};
            glUniform1f(point_size_uniform_location, _point_size);

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
                    "texturing_mode2"
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

        std::string _vertex_shader_source;
        std::string _fragment_shader_source;

        int _previous_directional_light_count{1};
        int _previous_point_light_count{1};
        int _previous_spot_light_count{0};
    };
}

#endif
