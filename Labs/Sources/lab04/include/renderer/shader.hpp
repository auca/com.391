#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <vector>
#include <utility>
#include <map>

namespace aur {
    class Shader {
    public:
        Shader(
            std::string vertex_shader_source,
            std::string fragment_shader_source,
            const std::vector<std::string> &attributes = {},
            const std::vector<std::string> &uniforms = {}
        ) : _vertex_shader_source{std::move(vertex_shader_source)},
            _fragment_shader_source{std::move(fragment_shader_source)} {
            for (const auto &uniform : uniforms) {
                _uniforms[uniform] = -1;
            }
            for (const auto &attribute : attributes) {
                _attributes[attribute] = -1;
            }
        }

        virtual ~Shader() = default;

        std::map<std::string, int> &get_attributes() {
            return _attributes;
        }

        std::map<std::string, int> &get_uniforms() {
            return _uniforms;
        }

        const std::map<std::string, int> &get_attributes() const {
            return _attributes;
        }

        const std::map<std::string, int> &get_uniforms() const {
            return _uniforms;
        }

        int get_program() const {
            return _program;
        }

        bool is_dead() const {
            return _dead;
        }

        bool is_compiled() const {
            return _program != -1;
        }

        virtual void compile() = 0;

    protected:
        std::string _vertex_shader_source;
        std::string _fragment_shader_source;

        std::map<std::string, int> _attributes;
        std::map<std::string, int> _uniforms;

        bool _dead{false};
        int _program{-1};
    };
}

#endif
