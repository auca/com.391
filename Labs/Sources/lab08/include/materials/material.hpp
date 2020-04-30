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
    public:
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

        enum FogType {
            Linear,
            Exp,
            Exp2
        };

        enum FogDepth {
            Planar,
            PlanarAbsolute,
            Radial
        };

        [[nodiscard]] const std::shared_ptr<Shader> &get_shader() const
        {
            return _shader;
        }

        virtual ~Material() = default;

        [[nodiscard]] float get_line_width() const {
            return _line_width;
        }

        void set_line_width(float line_width) {
            _line_width = line_width;
        }

        [[nodiscard]] bool prefer_line_width_from_geometry() const {
            return _prefer_line_width_from_geometry;
        }

        void set_prefer_line_width_from_geometry(bool prefer_line_width_from_geometry) {
            _prefer_line_width_from_geometry = prefer_line_width_from_geometry;
        }

        [[nodiscard]] bool is_point_sizing_enabled() const {
            return _point_sizing_enabled;
        }

        void set_point_sizing_enabled(bool point_sizing_enabled) {
            _point_sizing_enabled = point_sizing_enabled;
        }

        [[nodiscard]] float get_point_size() const {
            return _point_size;
        }

        void set_point_size(float point_size) {
            _point_size = point_size;
        }

        [[nodiscard]] bool prefer_point_size_from_geometry() const {
            return _prefer_point_size_from_geometry;
        }

        void set_prefer_point_size_from_geometry(bool prefer_point_size_from_geometry) {
            _prefer_point_size_from_geometry = prefer_point_size_from_geometry;
        }

        [[nodiscard]] bool is_depth_mask_enabled() const {
            return _depth_mask_enabled;
        }

        void set_depth_mask_enabled(bool depth_mask_enabled) {
            _depth_mask_enabled = depth_mask_enabled;
        }

        [[nodiscard]] bool is_depth_test_enabled() const {
            return _depth_test_enabled;
        }

        void set_depth_test_enabled(bool depth_test_enabled) {
            _depth_test_enabled = depth_test_enabled;
        }

        [[nodiscard]] DepthTestFunction get_depth_test_function() const {
            return _depth_test_function;
        }

        void set_depth_test_function(DepthTestFunction depth_test_function) {
            _depth_test_function = depth_test_function;
        }

        [[nodiscard]] bool is_blending_enabled() const {
            return _blending_enabled;
        }

        void set_blending_enabled(bool blending_enabled) {
            _blending_enabled = blending_enabled;
        }

        [[nodiscard]] BlendingEquation get_color_blending_equation() const {
            return _color_blending_equation;
        }

        void set_color_blending_equation(BlendingEquation color_blending_equation) {
            _color_blending_equation = color_blending_equation;
        }

        [[nodiscard]] BlendingEquation get_alpha_blending_equation() const {
            return _alpha_blending_equation;
        }

        void set_alpha_blending_equation(BlendingEquation alpha_blending_equation) {
            _alpha_blending_equation = alpha_blending_equation;
        }

        [[nodiscard]] BlendingFunction get_source_color_blending_function() const {
            return _source_color_blending_function;
        }

        void set_source_color_blending_function(BlendingFunction source_color_blending_function) {
            _source_color_blending_function = source_color_blending_function;
        }

        [[nodiscard]] BlendingFunction get_source_alpha_blending_function() const {
            return _source_alpha_blending_function;
        }

        void set_source_alpha_blending_function(BlendingFunction source_alpha_blending_function) {
            _source_alpha_blending_function = source_alpha_blending_function;
        }

        [[nodiscard]] BlendingFunction get_destination_color_blending_function() const {
            return _destination_color_blending_function;
        }

        void set_destination_color_blending_function(BlendingFunction destination_color_blending_function) {
            _destination_color_blending_function = destination_color_blending_function;
        }

        [[nodiscard]] BlendingFunction get_destination_alpha_blending_function() const {
            return _destination_alpha_blending_function;
        }

        void set_destination_alpha_blending_function(BlendingFunction destination_alpha_blending_function) {
            _destination_alpha_blending_function = destination_alpha_blending_function;
        }

        [[nodiscard]] const glm::vec4 &get_blending_constant_color() const {
            return _blending_constant_color;
        }

        void set_blending_constant_color(const glm::vec4 &blending_constant_color) {
            _blending_constant_color = blending_constant_color;
        }

        [[nodiscard]] bool is_face_culling_enabled() const {
            return _face_culling_enabled;
        }

        void set_face_culling_enabled(bool face_culling_enabled) {
            _face_culling_enabled = face_culling_enabled;
        }

        [[nodiscard]] CullFaceMode get_cull_face_mode() const {
            return _cull_face_mode;
        }

        void set_cull_face_mode(CullFaceMode cull_face_mode) {
            _cull_face_mode = cull_face_mode;
        }

        [[nodiscard]] FrontFaceOrder get_front_face_order() const {
            return _front_face_order;
        }

        void set_front_face_order(FrontFaceOrder front_face_order) {
            _front_face_order = front_face_order;
        }

        [[nodiscard]] bool is_polygon_offset_enabled() const {
            return _polygon_offset_enabled;
        }

        void set_polygon_offset_enabled(bool polygon_offset_enabled) {
            _polygon_offset_enabled = polygon_offset_enabled;
        }

        [[nodiscard]] float get_polygon_offset_factor() const {
            return _polygon_offset_factor;
        }

        void set_polygon_offset_factor(float polygon_offset_factor) {
            _polygon_offset_factor = polygon_offset_factor;
        }

        [[nodiscard]] float get_polygon_offset_units() const {
            return _polygon_offset_units;
        }

        void set_polygon_offset_units(float polygon_offset_units) {
            _polygon_offset_units = polygon_offset_units;
        }

        [[nodiscard]] bool is_fog_enabled() const
        {
            return _fog_enabled;
        }

        void set_fog_enabled(bool fog_enabled)
        {
            _fog_enabled = fog_enabled;
        }

        [[nodiscard]] FogType get_fog_type() const
        {
            return _fog_type;
        }

        void set_fog_type(FogType fog_type)
        {
            _fog_type = fog_type;
        }

        [[nodiscard]] FogDepth get_fog_depth() const
        {
            return _fog_depth;
        }

        void set_fog_depth(FogDepth fog_depth)
        {
            _fog_depth = fog_depth;
        }

        [[nodiscard]] const glm::vec3 &get_fog_color() const
        {
            return _fog_color;
        }

        void set_fog_color(const glm::vec3 &fog_color)
        {
            _fog_color = fog_color;
        }

        [[nodiscard]] float get_fog_near_plane() const
        {
            return _fog_near_plane;
        }

        void set_fog_near_plane(float fog_near_plane)
        {
            _fog_near_plane = fog_near_plane;
        }

        [[nodiscard]] float get_fog_far_plane() const
        {
            return _fog_far_plane;
        }

        void set_fog_far_plane(float fog_far_plane)
        {
            _fog_far_plane = fog_far_plane;
        }

        [[nodiscard]] float get_fog_density() const
        {
            return _fog_density;
        }

        void set_fog_density(float fog_density)
        {
            _fog_density = fog_density;
        }

        virtual void update(std::shared_ptr<Scene> scene, std::shared_ptr<Mesh> mesh) = 0;

        virtual void use() = 0;

    protected:
        std::shared_ptr<Shader> _shader;

        float _line_width{1.0f};
        bool _prefer_line_width_from_geometry{false};

        bool _point_sizing_enabled{false};
        float _point_size{1.0f};
        bool _prefer_point_size_from_geometry{false};

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

        bool _fog_enabled{false};
        FogType _fog_type{Exp2};
        FogDepth _fog_depth{Radial};
        glm::vec3 _fog_color{1.0f};
        float _fog_near_plane{1.0f};
        float _fog_far_plane{100.0f};
        float _fog_density{0.00042f};
    };
}

#endif
