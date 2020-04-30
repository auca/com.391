#include "aur.hpp"

static const float CAMERA_SPEED{0.1f};
static const float CAMERA_ROT_SPEED{0.05f};
static const float PLANE_ROT_SPEED{0.001f};

const glm::vec4 FORWARD{0.0f, 0.0f, 1.0f, 0.0f};

[[noreturn]]
int main(int argc, char **argv)
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur", 0, 0);

    auto[plane1_indices, plane1_vertices] = geometry_generators::generate_plane_geometry_data(20, 20, 2, 2);
    auto plane1_geometry = std::make_shared<ES2Geometry>(plane1_indices, plane1_vertices);
    auto plane1_material = std::make_shared<ES2PhongMaterial>();
    auto[image1_data, image1_width, image1_height, image1_channels] = file_utilities::read_image_file("data/images/checkerboard.png");
    auto texture1 = std::make_shared<ES2Texture>(image1_data, image1_width, image1_height, image1_channels);
    plane1_material->set_texture_1(texture1);
    auto plane1 = std::make_shared<Mesh>(plane1_geometry, plane1_material);
    plane1->set_position(glm::vec3(0.0f, 0.0f, -10.0f));
    plane1->set_rotation(glm::vec3(0.0f, 0.0f, 0.0f));

    auto[plane2_indices, plane2_vertices] = geometry_generators::generate_plane_geometry_data(20, 20, 2, 2);
    auto plane2_geometry = std::make_shared<ES2Geometry>(plane2_indices, plane2_vertices);
    auto plane2_material = std::make_shared<ES2PhongMaterial>();
    plane2_material->set_texture_1(texture1);
    plane2_material->set_emission_color(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
    auto plane2 = std::make_shared<Mesh>(plane2_geometry, plane2_material);
    plane2->set_position(glm::vec3(0.0f, -10.0f, 0.0f));
    plane2->set_rotation(glm::vec3(-M_PI / 2, 0.0f, 0.0f));

    auto[sphere1_indices, sphere1_vertices] = geometry_generators::generate_sphere_geometry_data(1.0f, 20, 20);
    auto sphere1_geometry = std::make_shared<ES2Geometry>(sphere1_indices, sphere1_vertices);
    auto sphere1_material = std::make_shared<ES2PhongMaterial>();
    sphere1_material->set_diffuse_color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    sphere1_material->set_specular_exponent(40.f);
    auto[image2_data, image2_width, image2_height, image2_channels] = file_utilities::read_image_file("data/images/checkerboard.png");
    auto texture2 = std::make_shared<ES2Texture>(image2_data, image2_width, image2_height, image2_channels);
    sphere1_material->set_texture_1(texture2);
    auto sphere1 = std::make_shared<Mesh>(sphere1_geometry, sphere1_material);
    sphere1->set_position(glm::vec3(0.0f, 0.0f, 0.0f));

    auto[lamp_indices, lamp_vertices] = geometry_generators::generate_sphere_geometry_data(0.2f, 20, 20);
    auto lamp_sphere_geometry = std::make_shared<ES2Geometry>(lamp_indices, lamp_vertices);
    auto lamp_material = std::make_shared<ES2ConstantMaterial>();
    lamp_material->set_emission_color(glm::vec4(1.0f));
    auto lamp1 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);
    auto lamp2 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);

    std::vector<std::shared_ptr<Object>> objects{plane1, plane2, sphere1};
    auto scene = std::make_shared<Scene>(objects);

    auto point_light1 = std::make_shared<PointLight>();
    auto point_light2 = std::make_shared<PointLight>();
    point_light1->set_intensity(0.45f);
    point_light1->set_z(10.0f);
    point_light1->set_y(2.0f);
    point_light1->set_two_sided(true);
    point_light1->add_child(lamp1);
    point_light2->set_intensity(0.45f);
    point_light1->set_z(10.0f);
    point_light2->set_y(2.0f);
    point_light2->set_two_sided(true);
    point_light2->add_child(lamp2);
    scene->get_root()->add_child(point_light1);
    scene->get_root()->add_child(point_light2);
    scene->get_point_lights().push_back(point_light1);
    scene->get_point_lights().push_back(point_light2);

    auto camera = scene->get_camera();
    camera->set_z(8.0f);

    window->set_on_key_down([&](int key) {
        switch (key) {
            case SDLK_w: camera->add_to_rotation_x(-CAMERA_ROT_SPEED); break;
            case SDLK_a: camera->add_to_rotation_y(CAMERA_ROT_SPEED); break;
            case SDLK_s: camera->add_to_rotation_x(CAMERA_ROT_SPEED); break;
            case SDLK_d: camera->add_to_rotation_y(-CAMERA_ROT_SPEED); break;
            case SDLK_e: camera->add_to_y(CAMERA_ROT_SPEED); break;
            case SDLK_q: camera->add_to_y(-CAMERA_ROT_SPEED); break;
            case SDLK_UP: camera->add_to_position(-glm::vec3(camera->get_model_matrix() * FORWARD * CAMERA_SPEED)); break;
            case SDLK_DOWN: camera->add_to_position(glm::vec3(camera->get_model_matrix() * FORWARD * CAMERA_SPEED)); break;
            case SDLK_ESCAPE: exit(0);
            default: break;
        }
    });

    bool plane1_rotation_enabled{false};
    glm::vec4 emission_color{plane1_material->get_emission_color()};
    bool texture1_enabled{true};
    Texture::Mode texture1_texturing_mode{Texture::Mode::Modulation};
    Texture::FilterType texture1_magnification_filter_type{Texture::FilterType::Nearest};
    Texture::FilterType texture1_minification_filter_type{Texture::FilterType::Nearest};
    Texture::WrapMode texture1_wrap_mode_s{Texture::WrapMode::Repeat};
    Texture::WrapMode texture1_wrap_mose_t{Texture::WrapMode::Repeat};
    bool texture1_transformation_matrix_enabled{false};
    glm::mat4 texture1_transformation_matrix{1.0f};
    int texture1_anisotropy{0};
    bool texture1_mipmaps_enabled{true};

    bool texture2_enabled{false};
    Texture::Mode texture2_texturing_mode{Texture::Mode::Modulation};
    Texture::FilterType texture2_magnification_filter_type{Texture::FilterType::Nearest};
    Texture::FilterType texture2_minification_filter_type{Texture::FilterType::Nearest};
    Texture::WrapMode texture2_wrap_mode_s{Texture::WrapMode::Repeat};
    Texture::WrapMode texture2_wrap_mose_t{Texture::WrapMode::Repeat};
    bool texture2_transformation_matrix_enabled{false};
    glm::mat4 texture2_transformation_matrix{1.0f};
    int texture2_anisotropy{0};
    bool texture2_mipmaps_enabled{true};

    bool sphere_texture_enabled{false};
    float sphere_z = sphere1->get_z();
    glm::vec4 sphere_diffuse_color  = sphere1_material->get_diffuse_color();
    glm::vec3 sphere_specular_color = sphere1_material->get_specular_color();
    float sphere_specular_exponent = sphere1_material->get_specular_exponent();
    glm::vec4 sphere_emission_color = sphere1_material->get_emission_color();
    glm::vec3 sphere_ambient_color  = sphere1_material->get_ambient_color();
    glm::vec4 sphere_blending_color  = sphere1_material->get_blending_constant_color();
    bool sphere_depth_mask_enabled = sphere1_material->is_depth_mask_enabled();
    bool sphere_depth_test_enabled = sphere1_material->is_depth_test_enabled();
    Material::DepthTestFunction sphere_depth_test_function = sphere1_material->get_depth_test_function();
    bool sphere_face_culling_enabled = sphere1_material->is_face_culling_enabled();
    Material::CullFaceMode sphere_cull_face_mode = sphere1_material->get_cull_face_mode();
    Material::FrontFaceOrder sphere_front_face_order = sphere1_material->get_front_face_order();

    bool sphere_blending_enabled = sphere1_material->is_blending_enabled();
    Material::BlendingEquation sphere_color_blending_equation = sphere1_material->get_color_blending_equation();
    Material::BlendingEquation sphere_alpha_blending_equation = sphere1_material->get_alpha_blending_equation();
    Material::BlendingFunction sphere_source_color_blending_function = sphere1_material->get_source_color_blending_function();
    Material::BlendingFunction sphere_source_alpha_blending_function = sphere1_material->get_source_alpha_blending_function();
    Material::BlendingFunction sphere_destination_color_blending_function = sphere1_material->get_destination_color_blending_function();
    Material::BlendingFunction sphere_destination_alpha_blending_function = sphere1_material->get_destination_alpha_blending_function();

    bool fog_enabled{false};
    Material::FogType fog_type{Material::FogType::Linear};
    Material::FogDepth fog_depth{Material::FogDepth::Planar};
    glm::vec3 fog_color{1.0f};
    float fog_near_plane{1.0f};
    float fog_far_plane{100.0f};
    float fog_density{0.00042f};

    float point_light_angle1 = 0.0f;
    float point_light_angle2 = 0.0f;
    float point_light_radius1 = 8.0f;
    float point_light_radius2 = 8.5f;

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::Begin("Parameters", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
        {
            if (ImGui::CollapsingHeader("Texture Parameters ")) {
                ImGui::Checkbox("Rotate", &plane1_rotation_enabled);
                ImGui::InputFloat4("Emission Color", glm::value_ptr(emission_color), "%.2f");

                ImGui::Checkbox("Enabled", &texture1_enabled);
                ImGui::Combo(
                    "Texturing Mode", reinterpret_cast<int *>(&texture1_texturing_mode),
                    "Addition\0Subtraction\0ReverseSubtraction\0Modulation\0Decaling\0"
                );
                ImGui::Combo(
                    "First Coordinate Wrap Mode", reinterpret_cast<int *>(&texture1_wrap_mode_s),
                    "Repeat\0Mirrored Repeat\0Clamp To Edge\0"
                );
                ImGui::Combo(
                    "Second Coordinate Wrap Mode", reinterpret_cast<int *>(&texture1_wrap_mose_t),
                    "Repeat\0Mirrored Repeat\0Clamp To Edge\0"
                );
                ImGui::Combo(
                    "Magnification Filter", reinterpret_cast<int *>(&texture1_magnification_filter_type),
                    "Nearest\0Linear\0Nearest Mipmap Nearest\0Nearest Mipmap Linear\0Linear Mipmap Nearest\0Linear Mipmap Linear\0"
                );
                ImGui::Combo(
                    "Minification Filter", reinterpret_cast<int *>(&texture1_minification_filter_type),
                    "Nearest\0Linear\0Nearest Mipmap Nearest\0Nearest Mipmap Linear\0Linear Mipmap Nearest\0Linear Mipmap Linear\0"
                );
                ImGui::Checkbox("Enable Transformation Matrix", &texture1_transformation_matrix_enabled);
                ImGui::InputFloat4("##5", glm::value_ptr(texture1_transformation_matrix), "%.2f");
                ImGui::InputFloat4("##6", glm::value_ptr(texture1_transformation_matrix) + 4, "%.2f");
                ImGui::InputFloat4("##7", glm::value_ptr(texture1_transformation_matrix) + 8, "%.2f");
                ImGui::InputFloat4("##8", glm::value_ptr(texture1_transformation_matrix) + 12, "%.2f");
                ImGui::SliderInt("Anisotropy", &texture1_anisotropy, 0, 16);
                ImGui::Checkbox("Use mipmaps", &texture1_mipmaps_enabled);
            }

            if (ImGui::CollapsingHeader("Texture 2 Parameters ")) {
                ImGui::Checkbox("Enabled##2", &texture2_enabled);
                ImGui::Combo(
                    "Texturing Mode##2", reinterpret_cast<int *>(&texture2_texturing_mode),
                    "Addition\0Subtraction\0ReverseSubtraction\0Modulation\0Decaling\0"
                );
                ImGui::Combo(
                    "First Coordinate Wrap Mode##2", reinterpret_cast<int *>(&texture2_wrap_mode_s),
                    "Repeat\0Mirrored Repeat\0Clamp To Edge\0"
                );
                ImGui::Combo(
                    "Second Coordinate Wrap Mode##2", reinterpret_cast<int *>(&texture2_wrap_mose_t),
                    "Repeat\0Mirrored Repeat\0Clamp To Edge\0"
                );
                ImGui::Combo(
                    "Magnification Filter##2", reinterpret_cast<int *>(&texture2_magnification_filter_type),
                    "Nearest\0Linear\0Nearest Mipmap Nearest\0Nearest Mipmap Linear\0Linear Mipmap Nearest\0Linear Mipmap Linear\0"
                );
                ImGui::Combo(
                    "Minification Filter##2", reinterpret_cast<int *>(&texture2_minification_filter_type),
                    "Nearest\0Linear\0Nearest Mipmap Nearest\0Nearest Mipmap Linear\0Linear Mipmap Nearest\0Linear Mipmap Linear\0"
                );
                ImGui::Checkbox("Enable Transformation Matrix##2", &texture2_transformation_matrix_enabled);
                ImGui::InputFloat4("##9", glm::value_ptr(texture2_transformation_matrix), "%.2f");
                ImGui::InputFloat4("##10", glm::value_ptr(texture2_transformation_matrix) + 4, "%.2f");
                ImGui::InputFloat4("##11", glm::value_ptr(texture2_transformation_matrix) + 8, "%.2f");
                ImGui::InputFloat4("##12", glm::value_ptr(texture2_transformation_matrix) + 12, "%.2f");
                ImGui::SliderInt("Anisotropy##2", &texture2_anisotropy, 0, 16);
                ImGui::Checkbox("Use mipmaps##2", &texture2_mipmaps_enabled);
            }

            if (ImGui::CollapsingHeader("Sphere Material Parameters ")) {
                ImGui::Checkbox("Enabled", &sphere_texture_enabled);

                ImGui::InputFloat4("Diffuse Color", glm::value_ptr(sphere_diffuse_color), "%.2f");
                ImGui::InputFloat3("Specular Color", glm::value_ptr(sphere_specular_color), "%.2f");
                ImGui::SliderFloat("Specular Exponent", &sphere_specular_exponent, 0.0f, 100.0f);
                ImGui::InputFloat4("Emission Color", glm::value_ptr(sphere_emission_color), "%.2f");
                ImGui::InputFloat3("Ambient Color", glm::value_ptr(sphere_ambient_color), "%.2f");
                ImGui::InputFloat4("Blending Color", glm::value_ptr(sphere_blending_color), "%.2f");

                ImGui::SliderFloat("Sphere Z", &sphere_z, -20.0f, 20.0f);

                //ImGui::Checkbox("Enable Depth Mask", &sphere_depth_mask_enabled);
                ImGui::Checkbox("Enable Depth Test", &sphere_depth_test_enabled);
                ImGui::Combo(
                    "Depth Test Function", reinterpret_cast<int *>(&sphere_depth_test_function),
                    "Never\0Always\0Less\0Lower or Equal\0Equal\0Greater\0Greater or Equal\0Not Equal\0"
                );

                ImGui::Checkbox("Enable Face Culling", &sphere_face_culling_enabled);
                ImGui::Combo(
                    "Cull Face Mode", reinterpret_cast<int *>(&sphere_cull_face_mode),
                    "Cull Front Faces\0Cull Back Faces\0Cull Front and Back Faces\0"
                );
                ImGui::Combo(
                    "Front Face Order", reinterpret_cast<int *>(&sphere_front_face_order),
                    "Clockwise\0Counterclockwise\0"
                );

                ImGui::Checkbox("Blending Enabled", &sphere_blending_enabled);
                ImGui::Combo(
                    "Color Blending Equation", reinterpret_cast<int *>(&sphere_color_blending_equation),
                    "Addition\0Subtraction\0Reverse Subtraction\0"
                );
                ImGui::Combo(
                    "Alpha Blending Equation", reinterpret_cast<int *>(&sphere_alpha_blending_equation),
                    "Addition\0Subtraction\0Reverse Subtraction\0"
                );
                ImGui::Combo(
                    "Source Color Blending Function", reinterpret_cast<int *>(&sphere_source_color_blending_function),
                    "Zero\0One\0SourceColor\0OneMinusSourceColor\0DestinationColor\0OneMinusDestinationColor\0SourceAlpha\0OneMinusSourceAlpha\0"
                    "DestinationAlpha\0OneMinusDestinationAlpha\0ConstantColor\0OneMinusConstantColor\0ConstantAlpha\0OneMinusConstantAlpha\0"
                    "SourceAlphaSaturate\0"
                );
                ImGui::Combo(
                    "Source Alpha Blending Function", reinterpret_cast<int *>(&sphere_source_alpha_blending_function),
                    "Zero\0One\0SourceColor\0OneMinusSourceColor\0DestinationColor\0OneMinusDestinationColor\0SourceAlpha\0OneMinusSourceAlpha\0"
                    "DestinationAlpha\0OneMinusDestinationAlpha\0ConstantColor\0OneMinusConstantColor\0ConstantAlpha\0OneMinusConstantAlpha\0"
                    "SourceAlphaSaturate\0"
                );
                ImGui::Combo(
                    "Destination Color Blending Function", reinterpret_cast<int *>(&sphere_destination_color_blending_function),
                    "Zero\0One\0SourceColor\0OneMinusSourceColor\0DestinationColor\0OneMinusDestinationColor\0SourceAlpha\0OneMinusSourceAlpha\0"
                    "DestinationAlpha\0OneMinusDestinationAlpha\0ConstantColor\0OneMinusConstantColor\0ConstantAlpha\0OneMinusConstantAlpha\0"
                    "SourceAlphaSaturate\0"
                );
                ImGui::Combo(
                    "Destination Alpha Blending Function", reinterpret_cast<int *>(&sphere_destination_alpha_blending_function),
                    "Zero\0One\0SourceColor\0OneMinusSourceColor\0DestinationColor\0OneMinusDestinationColor\0SourceAlpha\0OneMinusSourceAlpha\0"
                    "DestinationAlpha\0OneMinusDestinationAlpha\0ConstantColor\0OneMinusConstantColor\0ConstantAlpha\0OneMinusConstantAlpha\0"
                    "SourceAlphaSaturate\0"
                );
            }

            if (ImGui::CollapsingHeader("Fog Parameters ")) {
                ImGui::Checkbox("Enabled", &fog_enabled);
                ImGui::Combo(
                    "Fog Type", reinterpret_cast<int *>(&fog_type),
                    "Linear\0Exp\0Exp2\0"
                );
                ImGui::Combo(
                    "Fog Depth", reinterpret_cast<int *>(&fog_depth),
                    "Planar\0PlanarAbsolute\0Radial\0"
                );
                ImGui::InputFloat3("Fog Color", glm::value_ptr(fog_color), "%.2f");
                ImGui::SliderFloat("Fog Near Plane", &fog_near_plane, 0.01f, 100.0f);
                ImGui::SliderFloat("Fog Far Plane", &fog_far_plane, 0.01f, 100.0f);
                ImGui::SliderFloat("Fog Density", &fog_density, 0.01f, 1.0f);
            }
        }
        ImGui::End();

        if (plane1_rotation_enabled) {
            plane1->add_to_rotation_y(PLANE_ROT_SPEED);
        }
        plane1_material->set_emission_color(emission_color);
        texture1->set_enabled(texture1_enabled);
        texture1->set_mode(texture1_texturing_mode);
        texture1->set_wrap_mode_s(texture1_wrap_mode_s);
        texture1->set_wrap_mode_t(texture1_wrap_mose_t);
        texture1->set_magnification_filter(texture1_magnification_filter_type);
        texture1->set_minification_filter(texture1_minification_filter_type);
        texture1->set_transformation_enabled(texture1_transformation_matrix_enabled);
        texture1->set_transformation_matrix(texture1_transformation_matrix);
        texture1->set_anisotropy(static_cast<float>(texture1_anisotropy));
        texture1->set_mipmaps_enabled(texture1_mipmaps_enabled);

        texture2->set_enabled(texture2_enabled);
        texture2->set_mode(texture2_texturing_mode);
        texture2->set_wrap_mode_s(texture2_wrap_mode_s);
        texture2->set_wrap_mode_t(texture2_wrap_mose_t);
        texture2->set_magnification_filter(texture2_magnification_filter_type);
        texture2->set_minification_filter(texture2_minification_filter_type);
        texture2->set_transformation_enabled(texture2_transformation_matrix_enabled);
        texture2->set_transformation_matrix(texture2_transformation_matrix);
        texture2->set_anisotropy(static_cast<float>(texture2_anisotropy));
        texture2->set_mipmaps_enabled(texture2_mipmaps_enabled);

        sphere1_material->set_diffuse_color(sphere_diffuse_color);
        sphere1_material->set_specular_color(sphere_specular_color);
        sphere1_material->set_specular_exponent(sphere_specular_exponent);
        sphere1_material->set_emission_color(sphere_emission_color);
        sphere1_material->set_ambient_color(sphere_ambient_color);
        sphere1_material->set_blending_constant_color(sphere_blending_color);
        sphere1->set_z(sphere_z);
        sphere1_material->set_depth_mask_enabled(sphere_depth_mask_enabled);
        sphere1_material->set_depth_test_enabled(sphere_depth_test_enabled);
        sphere1_material->set_depth_test_function(sphere_depth_test_function);
        sphere1_material->set_face_culling_enabled(sphere_face_culling_enabled);
        sphere1_material->set_cull_face_mode(sphere_cull_face_mode);
        sphere1_material->set_front_face_order(sphere_front_face_order);
        sphere1_material->set_blending_enabled(sphere_blending_enabled);
        sphere1_material->set_color_blending_equation(sphere_color_blending_equation);
        sphere1_material->set_alpha_blending_equation(sphere_alpha_blending_equation);
        sphere1_material->set_source_color_blending_function(sphere_source_color_blending_function);
        sphere1_material->set_source_alpha_blending_function(sphere_source_alpha_blending_function);
        sphere1_material->set_destination_color_blending_function(sphere_destination_color_blending_function);
        sphere1_material->set_destination_alpha_blending_function(sphere_destination_alpha_blending_function);

        plane1_material->set_fog_enabled(fog_enabled);
        plane1_material->set_fog_type(fog_type);
        plane1_material->set_fog_depth(fog_depth);
        plane1_material->set_fog_color(fog_color);
        plane1_material->set_fog_near_plane(fog_near_plane);
        plane1_material->set_fog_far_plane(fog_far_plane);
        plane1_material->set_fog_density(fog_density);
        plane2_material->set_fog_enabled(fog_enabled);
        plane2_material->set_fog_type(fog_type);
        plane2_material->set_fog_depth(fog_depth);
        plane2_material->set_fog_color(fog_color);
        plane2_material->set_fog_near_plane(fog_near_plane);
        plane2_material->set_fog_far_plane(fog_far_plane);
        plane2_material->set_fog_density(fog_density);

        sphere1_material->set_fog_enabled(fog_enabled);
        sphere1_material->set_fog_type(fog_type);
        sphere1_material->set_fog_depth(fog_depth);
        sphere1_material->set_fog_color(fog_color);
        sphere1_material->set_fog_near_plane(fog_near_plane);
        sphere1_material->set_fog_far_plane(fog_far_plane);
        sphere1_material->set_fog_density(fog_density);

        point_light1->set_x(cosf(point_light_angle1) * point_light_radius1);
        point_light1->set_z(sinf(point_light_angle1) * point_light_radius1);
        point_light2->set_x(cosf(point_light_angle2) * point_light_radius2);
        point_light2->set_z(sinf(point_light_angle2) * point_light_radius2);
        point_light_angle1 += 0.01f;
        point_light_angle2 -= 0.01f;

        renderer.render();
    }
}
