#ifndef ES2_RENDERER_HPP
#define ES2_RENDERER_HPP

#include "renderer/renderer.hpp"
#include "objects/object.hpp"
#include "objects/mesh.hpp"

#include <GL/glew.h>
#include <SDL.h>
#include <glm/glm.hpp>

#include <queue>
#include <memory>

namespace aur
{
    class ES2Renderer : public Renderer
    {
    public:
        ES2Renderer(const std::shared_ptr<Scene> &scene, const std::shared_ptr<Window> &window)
            : Renderer(scene, window)
        {
            glm::vec4 clear_color = scene->get_clear_color();
            glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            glEnable(GL_PROGRAM_POINT_SIZE);
            glCullFace(GL_BACK);
            glFrontFace(GL_CW);

            std::queue<std::shared_ptr<Object>> queue;
            queue.push(scene->get_root());
            while (!queue.empty()) {
                const auto object = queue.front();
                queue.pop();
                if (auto mesh = std::dynamic_pointer_cast<Mesh>(object)) {
                    const auto &geometry = mesh->get_geometry();
                    const auto &material = mesh->get_material();

                    material->use();
                    material->update(scene, mesh);
                    geometry->update(*mesh->get_material());
                }

                for (const auto &child: object->get_children()) { queue.push(child); }
            }
        }

        void render() final
        {
            glViewport(0, 0, static_cast<GLsizei>(window->get_width()), static_cast<GLsizei>(window->get_height()));
            glClear(static_cast<unsigned int>(GL_COLOR_BUFFER_BIT) | static_cast<unsigned int>(GL_DEPTH_BUFFER_BIT));

            auto camera = scene->get_camera();
            if (camera->should_receive_aspect_ratio_from_renderer()) {
                float aspect_ratio = fabsf(static_cast<float>(window->get_width()) / static_cast<float>(window->get_height()));
                camera->set_aspect_ratio(aspect_ratio);
            }

            std::queue<std::shared_ptr<Object>> queue;
            queue.push(scene->get_root());
            while (!queue.empty()) {
                const auto object = queue.front();
                queue.pop();
                if (auto mesh = std::dynamic_pointer_cast<Mesh>(object)) {
                    auto geometry = mesh->get_geometry();
                    auto material = mesh->get_material();

                    material->use();
                    material->update(scene, mesh);
                    geometry->use();

                    glLineWidth(geometry->get_line_width());
                    glDrawElements(
                        _convert_geometry_type_to_es2_geometry_type(geometry->get_type()),
                        static_cast<GLsizei>(geometry->get_indices().size()),
                        GL_UNSIGNED_INT,
                        nullptr
                    );
                }

                for (const auto &child: object->get_children()) { queue.push(child); }
            }

            window->swap();
        }

    private:
        static GLenum _convert_geometry_type_to_es2_geometry_type(Geometry::Type type)
        {
            switch (type) {
                case Geometry::Type::Points:
                    return GL_POINTS;
                case Geometry::Type::Lines:
                    return GL_LINES;
                case Geometry::Type::LineLoop:
                    return GL_LINE_LOOP;
                case Geometry::Type::LineStrip:
                    return GL_LINE_STRIP;
                case Geometry::Type::Triangles:
                    return GL_TRIANGLES;
                case Geometry::Type::TriangleFan:
                    return GL_TRIANGLE_FAN;
                case Geometry::Type::TriangleStrip:
                    return GL_TRIANGLE_STRIP;
                default:
                    return GL_TRIANGLES;
            }
        }
    };
}

#endif
