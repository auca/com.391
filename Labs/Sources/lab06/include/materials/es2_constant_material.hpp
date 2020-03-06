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

namespace aur {
    class ES2ConstantMaterial : public ConstantMaterial {
    public:
        ES2ConstantMaterial() {
            std::string vertex_shader_source = FileUtilities::read_text_file("data/shaders/es2_constant_shader.vert");
            std::string fragment_shader_source = FileUtilities::read_text_file("data/shaders/es2_constant_shader.frag");
            std::vector<std::string> attributes {
                "position",
                "color",
                "texture_coordinates"
            };
            std::vector<std::string> uniforms {
                "model_view_projection_matrix",
                "emission_color",
                "point_size",

                "texture_sampler"
            };

            _shader = std::make_shared<ES2Shader>(vertex_shader_source, fragment_shader_source, attributes, uniforms);
        }

        void update(std::shared_ptr<Scene> scene, std::shared_ptr<Mesh> mesh) final {
            if (_shader->is_dead()) {
                return;
            } else if (!_shader->is_compiled()) {
                _shader->compile(); if (_shader->is_dead()) { return; }
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

            if (_texture) {
                int texture_sampler_uniform_location{_shader->get_uniforms().at("texture_sampler")};
                glUniform1i(texture_sampler_uniform_location, 0);
            }
        }

        void use() final {
            if (_texture) {
                _texture->update();
            }
            _shader->use();
        }
    };
}

#endif
