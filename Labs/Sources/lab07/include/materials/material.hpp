#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "renderer/shader.hpp"
#include "scene/scene.hpp"
#include "objects/mesh.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace aur
{
    class Mesh;

    class Material
    {
        enum DepthTestFunction {
            Never,
            Always,
            Less,
            LowerOrEqual,
            Equal,
            Greater,
            GreaterOrEqual,
            NotEqual
        };

        enum BlendingEquation
        {
            Addition,
            Subtraction,
            ReverseSubtraction
        };

        enum BlendingFunction
        {
            Zero,
            One,
            SourceColor,
            OneMinusSourceColor,
            DestinationColor,
            OneMinusDestinationColor,
            SourceAlpha,
            OneMinusSourceAlpha,
            DestinationAlpha,
            OneMinusDestinationAlpha,
            ConstantColor,
            OneMinusConstantColor,
            ConstantAlpha,
            OneMinusConstantAlpha,
            SourceAlphaSaturate
        };

        enum CullFaceMode {
            CullFrontFaces,
            CullBackFaces,
            CullFrontAndBackFaces
        };

        enum FrontFaceOrder {
            Clockwise,
            Counterclockwise
        };

    public:
        [[nodiscard]] const std::shared_ptr<Shader> &get_shader() const
        {
            return _shader;
        }

        virtual ~Material() = default;

        virtual void update(std::shared_ptr<Scene> scene, std::shared_ptr<Mesh> mesh) = 0;

        virtual void use() = 0;

    protected:
        std::shared_ptr<Shader> _shader;

        float _line_width{1.0f};
        bool _prefer_line_width_from_geometry{false};

        bool _point_sizing_enabled{false};
        float _point_size{1.0f};
        bool _prefer_point_size_from_geometry{false};
        bool _round_points_enabled{false};

        bool _depth_mask_enabled{true};

        bool _depth_test_enabled{true};
        DepthTestFunction _depth_test_function{Less};

        bool _blending_enabled{false};
        BlendingEquation _color_blending_equation{Addition};
        BlendingEquation _alpha_blending_equation{Addition};
        BlendingFunction _source_color_blending_function{SourceAlpha};
        BlendingFunction _source_alpha_blending_function{SourceAlpha};
        BlendingFunction _destination_color_blending_function{OneMinusSourceAlpha};
        BlendingFunction _destination_alpha_blending_function{OneMinusSourceAlpha};
        glm::vec4 _blending_constant_color{0.0f};

        bool _face_culling_enabled{true};
        CullFaceMode _cull_face_mode{CullBackFaces};
        FrontFaceOrder _front_face_order{Clockwise};

        bool _polygon_offset_enabled{false};
        float _polygon_offset_factor{0.0f};
        float _polygon_offset_units{0.0f};
    };
}

#endif
