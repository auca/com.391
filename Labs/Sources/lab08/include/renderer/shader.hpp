#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <vector>
#include <utility>
#include <map>

namespace aur
{
    class Shader
    {
    public:
        Shader(
            std::string vertex_shader_source,
            std::string fragment_shader_source,
            const std::vector<std::string> &attributes = {},
            const std::vector<std::string> &uniforms = {}
        ) : _vertex_shader_source{std::move(vertex_shader_source)},
            _fragment_shader_source{std::move(fragment_shader_source)}
        {
            for (const auto &uniform : uniforms) {
                _uniforms[uniform] = -1;
            }
            for (const auto &attribute : attributes) {
                _attributes[attribute] = -1;
            }
        }

        virtual ~Shader() = default;

        [[nodiscard]] const std::string &get_vertex_shader_source() const
        {
            return _vertex_shader_source;
        }

        void set_vertex_shader_source(const std::string &vertex_shader_source)
        {
            _vertex_shader_source = vertex_shader_source;
        }

        [[nodiscard]] const std::string &get_fragment_shader_source() const
        {
            return _fragment_shader_source;
        }

        void set_fragment_shader_source(const std::string &fragment_shader_source)
        {
            _fragment_shader_source = fragment_shader_source;
        }

        std::map<std::string, int> &get_attributes()
        {
            return _attributes;
        }

        [[nodiscard]] const std::map<std::string, int> &get_attributes() const
        {
            return _attributes;
        }

        std::map<std::string, int> &get_uniforms()
        {
            return _uniforms;
        }

        [[nodiscard]] const std::map<std::string, int> &get_uniforms() const
        {
            return _uniforms;
        }

        [[nodiscard]] bool is_dead() const
        {
            return _dead;
        }

        [[nodiscard]] bool is_compiled() const
        {
            return _program != -1;
        }

        virtual void compile() = 0;

        virtual void cleanup() = 0;

        virtual void use() = 0;

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
