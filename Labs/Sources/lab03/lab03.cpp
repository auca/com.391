#include "scene.hpp"
#include "mesh.hpp"
#include "geometry.hpp"
#include "sdl_window.hpp"
#include "es2_renderer.hpp"
#include "es2_geometry.hpp"
#include "es2_constant_material.hpp"

#include <SDL.h>
#include <glm/glm.hpp>

static const float CAMERA_SPEED { 0.01f };
static const float CAMERA_ROT_SPEED { 0.01f };
static const float TRIANGLE_ROT_SPEED { 0.01f };

static const glm::vec4 FORWARD {0.0f, 0.0f, 1.0f, 0.0f };

int main(int argc, char **argv)
{
    SDLWindow window { "lab03", 500, 500 };

    std::vector<Vertex> vertices {
        Vertex { {-0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        Vertex { { 0.0f,  0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        Vertex { { 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
    };
    Geometry *geometry = new ES2Geometry { vertices };
    Material *material = new ES2ConstantMaterial { };
    Mesh *triangle1 = new Mesh { geometry, material,glm::vec3 { -0.5f, 0.0f, 1.0f } };
    Mesh *triangle2 = new Mesh { geometry, material,glm::vec3 { +0.5f, 0.0f, 1.0f } };

    std::vector<Object *> objects { triangle1, triangle2 };
    Scene scene { objects };

    Camera &camera = scene.get_camera();
    camera.set_field_of_view(1.13f);
    camera.set_aspect_ratio(fabsf((float) window.get_width() / (float) window.get_height()));
    camera.get_position().z = -0.5f;
    camera.get_rotation().y = M_PI;

    ES2Renderer renderer;
    renderer.setup(scene, window);

    for (;;) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                goto end;
            } else {
                switch (event.key.keysym.sym) {
                    case SDLK_w: {
                        camera.get_rotation().x -= CAMERA_ROT_SPEED;
                        break;
                    }
                    case SDLK_a: {
                        camera.get_rotation().y += CAMERA_ROT_SPEED;
                        break;
                    }
                    case SDLK_s: {
                        camera.get_rotation().x += CAMERA_ROT_SPEED;
                        break;
                    }
                    case SDLK_d: {
                        camera.get_rotation().y -= CAMERA_ROT_SPEED;
                        break;
                    }
                    case SDLK_UP: {
                        glm::vec4 dir = camera.get_model_matrix() * FORWARD * CAMERA_SPEED;
                        camera.get_position().x -= dir.x;
                        camera.get_position().y -= dir.y;
                        camera.get_position().z -= dir.z;
                        break;
                    }
                    case SDLK_DOWN: {
                        glm::vec4 dir = camera.get_model_matrix() * FORWARD * CAMERA_SPEED;
                        camera.get_position().x += dir.x;
                        camera.get_position().y += dir.y;
                        camera.get_position().z += dir.z;
                        break;
                    }
                }
            }
        }

        renderer.render(scene, window);
    }

end:
    return 0;
}

