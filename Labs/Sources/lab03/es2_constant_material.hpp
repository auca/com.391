#ifndef CONSTANT_MATERIAL_HPP
#define CONSTANT_MATERIAL_HPP

#include "material.hpp"
#include "utilities.hpp"
#include "es2_shader.hpp"

#include <GL/glew.h>
#include <SDL.h>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>

class ES2ConstantMaterial : public Material {
public:
    ES2ConstantMaterial() {
        std::string vertex_shader_source = FileUtilities::read_text_file("constant_shader.vert");
        std::string fragment_shader_source = FileUtilities::read_text_file("constant_shader.frag");
        std::vector<std::string> attributes { "position", "color" };
        std::vector<std::string> uniforms { "model_view_projection_matrix" };

        _shader = std::shared_ptr<Shader> { new ES2Shader(vertex_shader_source, fragment_shader_source, attributes, uniforms) };
    }

    void update(glm::mat4 &mvp_matrix) final {
        if (_shader->get_program() == -1) {
            _shader->compile();
        }

        int mvp_matrix_uniform_location { _shader->get_uniforms().at("model_view_projection_matrix") };
        glUniformMatrix4fv(
            mvp_matrix_uniform_location,
            1, GL_FALSE,
            glm::value_ptr(mvp_matrix)
        );
    }

    void use() final {
        glUseProgram(_shader->get_program());
    }
};

#endif
