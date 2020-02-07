#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <vector>
#include <map>

class Shader {
public:
    Shader(
        std::string &vertex_shader_source,
        std::string &fragment_shader_source,
        const std::vector<std::string> &attributes = {},
        const std::vector<std::string> &uniforms = {}
    ) : _vertex_shader_source { vertex_shader_source },
        _fragment_shader_source { fragment_shader_source } {
        for (const auto& uniform : uniforms) {
            _uniforms[uniform] = -1;
        }
        for (const auto& attribute : attributes) {
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

    virtual void compile() = 0;

protected:
    std::string _vertex_shader_source;
    std::string _fragment_shader_source;

    std::map<std::string, int> _attributes;
    std::map<std::string, int> _uniforms;

    int _program { -1 };
};

#endif
