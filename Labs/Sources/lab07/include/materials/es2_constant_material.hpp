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
                "model_view_projection_matrix",
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
                "texturing_mode2"
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

            glm::mat4 mvp_matrix = scene->get_camera()->get_view_projection_matrix() * mesh->get_world_matrix();
            int mvp_matrix_uniform_location{_shader->get_uniforms().at("model_view_projection_matrix")};
            glUniformMatrix4fv(
                mvp_matrix_uniform_location,
                1, GL_FALSE,
                glm::value_ptr(mvp_matrix)
            );

            int point_size_uniform_location{_shader->get_uniforms().at("point_size")};
            glUniform1f(point_size_uniform_location, _point_size);

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
    };
}

#endif
