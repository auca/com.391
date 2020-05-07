#include "aur.hpp"

static const float CAMERA_SPEED{0.3f};
static const float CAMERA_SENSITIVITY{0.001f};

const glm::vec4 FORWARD{0.0f, 0.0f, 1.0f, 0.0f};
const glm::vec4 RIGHT{1.0f, 0.0f, 0.0f, 0.0f};

[[noreturn]]
int main(int argc, char **argv)
{
    using namespace aur;

    // Window

    auto window = std::make_shared<SDLWindow>("aur", 0, 0);
    window->set_capture_mouse_enabled(true);
    window->set_relative_mouse_mode_enabled(true);

    // Room Ground

    auto[room_ground_indices, room_ground_vertices] = geometry_generators::generate_plane_geometry_data(50, 50, 1, 1);
    auto room_ground_geometry = std::make_shared<ES2Geometry>(room_ground_indices, room_ground_vertices);
    auto room_ground_material = std::make_shared<ES2PhongMaterial>();
    room_ground_material->set_specular_exponent(1.0f);
    room_ground_material->set_specular_color(glm::vec3{0.0f});
    room_ground_material->set_diffuse_color(glm::vec4{0.25f});
    auto room_ground = std::make_shared<Mesh>(room_ground_geometry, room_ground_material);
    room_ground->set_position(glm::vec3(0.0f, -2.5f, 0.0f));
    room_ground->set_rotation(glm::vec3(-M_PI / 2.0f, 0.0f, 0.0f));

    // Monsters

    auto[image1_data, image1_width, image1_height, image1_channels] = file_utilities::read_image_file("data/images/headb1.png");
    auto texture1 = std::make_shared<ES2Texture>(image1_data, image1_width, image1_height, image1_channels);
    texture1->set_minification_filter(Texture::FilterType::Nearest);
    texture1->set_magnification_filter(Texture::FilterType::Nearest);
    texture1->set_mode(Texture::Mode::Modulation);

    auto[billboard1_indices, billboard1_vertices] = geometry_generators::generate_plane_geometry_data(9, 9, 1, 1);
    auto billboard1_geometry = std::make_shared<ES2Geometry>(billboard1_indices, billboard1_vertices);
    auto billboard1_material = std::make_shared<ES2ConstantMaterial>();
    billboard1_material->set_texture_1(texture1);
    billboard1_material->set_face_culling_enabled(false);
    billboard1_material->set_blending_enabled(true);
    billboard1_material->set_transparent(true);
    auto billboard1 = std::make_shared<Mesh>(billboard1_geometry, billboard1_material);
    billboard1->set_position(glm::vec3(-5.0f, 2.5f, 0.0f));
    billboard1->set_rotation(glm::vec3(0.0f, 0.0f, 0.0f));
    Sphere billboard1_sphere{billboard1->get_position(), 4.5};

    auto[billboard2_indices, billboard2_vertices] = geometry_generators::generate_plane_geometry_data(9, 9, 1, 1);
    auto billboard2_geometry = std::make_shared<ES2Geometry>(billboard2_indices, billboard2_vertices);
    auto billboard2_material = std::make_shared<ES2ConstantMaterial>();
    billboard2_material->set_texture_1(texture1);
    billboard2_material->set_face_culling_enabled(false);
    billboard2_material->set_blending_enabled(true);
    billboard2_material->set_transparent(true);
    auto billboard2 = std::make_shared<Mesh>(billboard2_geometry, billboard2_material);
    billboard2->set_position(glm::vec3(5.0f, 2.5f, 0.0f));
    billboard2->set_rotation(glm::vec3(0.0f, 0.0f, 0.0f));
    Sphere billboard2_sphere{billboard2->get_position(), 4.5};

    // Gun

    auto[image2_data, image2_width, image2_height, image2_channels] = file_utilities::read_image_file("data/images/shtga0.png");
    auto texture2 = std::make_shared<ES2Texture>(image2_data, image2_width, image2_height, image2_channels);
    texture2->set_minification_filter(Texture::FilterType::Nearest);
    texture2->set_magnification_filter(Texture::FilterType::Nearest);
    texture2->set_mode(Texture::Mode::Modulation);

    auto[overlay_indices, overlay_vertices] = geometry_generators::generate_plane_geometry_data(2, 2, 1, 1);
    auto overlay_geometry = std::make_shared<ES2Geometry>(overlay_indices, overlay_vertices);
    auto overlay_material = std::make_shared<ES2ConstantMaterial>();
    overlay_material->set_texture_1(texture2);
    overlay_material->set_blending_enabled(true);
    overlay_material->set_overlay(true);
    auto overlay = std::make_shared<Mesh>(overlay_geometry, overlay_material);
    overlay->set_position(glm::vec3(0.0f, -2.0f, 0.0f));

    // Lamps

    auto[lamp_indices, lamp_vertices] = geometry_generators::generate_sphere_geometry_data(0.2f, 20, 20);
    auto lamp_sphere_geometry = std::make_shared<ES2Geometry>(lamp_indices, lamp_vertices);
    auto lamp_material = std::make_shared<ES2ConstantMaterial>();
    auto lamp1 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);
    auto lamp2 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);
    auto lamp3 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);
    auto lamp4 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);

    std::vector<std::shared_ptr<Object>> objects{room_ground, billboard1, billboard2, overlay};
    auto scene = std::make_shared<Scene>(objects);

    // Point Lights

    auto point_light1 = std::make_shared<PointLight>();
    point_light1->set_intensity(4000.0f);
    point_light1->set_constant_attenuation(0.0f);
    point_light1->set_linear_attenuation(0.2f);
    point_light1->set_quadratic_attenuation(0.8f);
    point_light1->set_two_sided(true);
    point_light1->set_position(glm::vec3(-25.0f, 4.0f, 25.0f));
    point_light1->add_child(lamp1);
    scene->get_root()->add_child(point_light1);
    scene->get_point_lights().push_back(point_light1);

    auto point_light2 = std::make_shared<PointLight>();
    point_light2->set_intensity(4000.0f);
    point_light2->set_constant_attenuation(0.0f);
    point_light2->set_linear_attenuation(0.2f);
    point_light2->set_quadratic_attenuation(0.8f);
    point_light2->set_two_sided(true);
    point_light2->set_position(glm::vec3(25.0f, 4.0f, 25.0f));
    point_light2->add_child(lamp2);
    scene->get_root()->add_child(point_light2);
    scene->get_point_lights().push_back(point_light2);

    auto point_light3 = std::make_shared<PointLight>();
    point_light3->set_intensity(4000.0f);
    point_light3->set_constant_attenuation(0.0f);
    point_light3->set_linear_attenuation(0.2f);
    point_light3->set_quadratic_attenuation(0.8f);
    point_light3->set_two_sided(true);
    point_light3->set_position(glm::vec3(25.0f, 4.0f, -25.0f));
    point_light3->add_child(lamp3);
    scene->get_root()->add_child(point_light3);
    scene->get_point_lights().push_back(point_light3);

    auto point_light4 = std::make_shared<PointLight>();
    point_light4->set_intensity(4000.0f);
    point_light4->set_constant_attenuation(0.0f);
    point_light4->set_linear_attenuation(0.2f);
    point_light4->set_quadratic_attenuation(0.8f);
    point_light4->set_two_sided(true);
    point_light4->set_position(glm::vec3(-25.0f, 4.0f, -25.0f));
    point_light4->add_child(lamp4);
    scene->get_root()->add_child(point_light4);
    scene->get_point_lights().push_back(point_light4);

    // Camera

    auto camera = scene->get_camera();
    camera->set_position(glm::vec3(0.0f, 0.0f, 20.0f));
    camera->set_zoom(3.0f);

    // Input

    window->set_on_key_down([&](int key) {
        glm::mat4 model_matrix = camera->get_model_matrix();

        switch (key) {
            case SDLK_w: camera->add_to_position(-glm::vec3(model_matrix * FORWARD * CAMERA_SPEED)); break;
            case SDLK_a: camera->add_to_position(-glm::vec3(model_matrix * RIGHT * CAMERA_SPEED)); break;
            case SDLK_s: camera->add_to_position(glm::vec3(model_matrix * FORWARD * CAMERA_SPEED)); break;
            case SDLK_d: camera->add_to_position(glm::vec3(model_matrix * RIGHT * CAMERA_SPEED)); break;
            case SDLK_e: camera->add_to_y(CAMERA_SPEED); break;
            case SDLK_q: camera->add_to_y(-CAMERA_SPEED); break;
            case SDLK_ESCAPE: exit(0);
            default: break;
        }
    });

    window->set_on_mouse_move([&](int x, int y, int x_rel, int y_rel) {
        camera->add_to_rotation_y(static_cast<float>(-x_rel) * CAMERA_SENSITIVITY);
        camera->add_to_rotation_x(static_cast<float>(-y_rel) * CAMERA_SENSITIVITY);

        int cx = static_cast<int>(window->get_width() / 2);
        int cy = static_cast<int>(window->get_height() / 2);
        Ray ray = camera->world_ray_from_screen_point(cx, cy, static_cast<int>(window->get_width()), static_cast<int>(window->get_height()));

        auto[intersects, distance] = ray.intersects_with_sphere(billboard1_sphere);
        if (intersects) {
            billboard1_material->set_emission_color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        } else {
            billboard1_material->set_emission_color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        }

        auto[intersects2, distance2] = ray.intersects_with_sphere(billboard2_sphere);
        if (intersects2) {
            billboard2_material->set_emission_color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        } else {
            billboard2_material->set_emission_color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    });

    // Rendering

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        billboard1->billboard_toward_camera(camera);
        billboard2->billboard_toward_camera(camera);

        renderer.render();
    }
}
