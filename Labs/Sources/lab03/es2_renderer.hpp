#ifndef ES2RENDERER_HPP
#define ES2RENDERER_HPP

#include "renderer.hpp"

#include <GL/glew.h>
#include <SDL.h>
#include <glm/glm.hpp>

class ES2Renderer : public Renderer {
public:
    void setup(Scene &scene, Window &window) final {
        glm::vec4 clear_color = scene.get_clear_color();
        glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);

        for (auto &object : scene.get_objects()) {
            Mesh *mesh = dynamic_cast<Mesh *>(object.get());

            const auto& geometry = mesh->get_geometry();
            const auto& material = mesh->get_material();
            glm::mat4 mvp_matrix { 1.0f };
            material->update(mvp_matrix);
            geometry->update(*mesh->get_material());
        }
    }

    void render(Scene &scene, Window &window) final {
        glViewport(0, 0, (GLsizei) window.get_width(), (GLsizei) window.get_height());

        Camera &camera = scene.get_camera();
        camera.update_model_matrix();
        camera.update_view_matrix();
        camera.update_projection_matrix();
        camera.update_view_projection_matrix();

        for (auto &object : scene.get_objects()) {
            if (auto mesh = std::dynamic_pointer_cast<Mesh>(object)) {
                auto geometry = mesh->get_geometry();
                auto material = mesh->get_material();

                mesh->update_model_matrix();
                glm::mat4 mvp_matrix = camera.get_view_projection_matrix() * object->get_model_matrix();
                material->update(mvp_matrix);

                material->use();
                geometry->bind();

                glClear(GL_COLOR_BUFFER_BIT);
                glLineWidth(geometry->get_line_width());
                glDrawArrays(geometry->get_type(), 0, geometry->get_vertices().size());
            }
        }

        window.swap();
    }
};

#endif
