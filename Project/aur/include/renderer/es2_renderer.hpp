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

            glEnable(GL_PROGRAM_POINT_SIZE);

            std::queue<std::shared_ptr<Object>> queue;
            queue.push(scene->get_root());
            while (!queue.empty()) {
                const auto object = queue.front(); queue.pop();
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

            std::vector<std::shared_ptr<Mesh>> opaque, transparent, overlays;
            std::queue<std::shared_ptr<Object>> queue;
            queue.push(scene->get_root());
            while (!queue.empty()) {
                const auto object = queue.front(); queue.pop();
                if (auto mesh = std::dynamic_pointer_cast<Mesh>(object)) {
                    auto material = mesh->get_material();
                    if (material->is_overlay()) {
                        overlays.push_back(mesh);
                    } else if (material->is_transparent()) {
                        transparent.push_back(mesh);
                    } else {
                        opaque.push_back(mesh);
                    }
                }

                for (const auto &child: object->get_children()) { queue.push(child); }
            }

            std::sort(std::begin(transparent), std::end(transparent), [&](const auto &a, const auto &b) {
                return glm::length(camera->get_world_position() - a->get_world_position()) >
                           glm::length(camera->get_world_position() - b->get_world_position());
            });
            std::sort(std::begin(overlays), std::end(overlays), [](const auto &a, const auto &b) {
                return a->get_material()->get_overlay_priority() > b->get_material()->get_overlay_priority();
            });

            for (auto &mesh : opaque) {
                _render_mesh(mesh);
            }
            for (auto &mesh : transparent) {
                _render_mesh(mesh);
            }
            for (auto &mesh : overlays) {
                _render_mesh(mesh);
            }

            window->swap();
        }

    private:
        void _render_mesh(const std::shared_ptr<Mesh> &mesh) const
        {
            auto geometry = mesh->get_geometry();
            auto material = mesh->get_material();

            material->use();
            material->update(scene, mesh);
            geometry->use();

            glDrawElements(
                _convert_geometry_type_to_es2_geometry_type(geometry->get_type()),
                static_cast<GLsizei>(geometry->get_indices().size()),
                GL_UNSIGNED_INT,
                nullptr
            );
        }

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
