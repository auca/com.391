#ifndef GEOMETRY_GENERATORS_HPP
#define GEOMETRY_GENERATORS_HPP

#include "geometries/vertex.hpp"

#include <utility>
#include <vector>
#include <cmath>

#include <glm/glm.hpp>

namespace aur::geometry_generators
{
    typedef std::pair<std::vector<unsigned int>, std::vector<Vertex>> geometry_data_type;

    geometry_data_type generate_triangle_geometry_data(float size = 1.0f)
    {
        std::vector<unsigned int> indices;
        std::vector<Vertex> vertices;

        const float radius = size * 0.5f;
        for (int i = 0; i < 3; ++i) {
            float angle{static_cast<float>(i) / 3.0f * 2.0f * static_cast<float>(M_PI) - static_cast<float>(M_PI) / 6.0f};
            float x{cosf(angle) * radius};
            float y{sinf(angle) * radius};
            float u{x};
            float v{y};
            vertices.push_back(Vertex{
                glm::vec3{x, y, 0.0f},
                glm::vec4{1.0f},
                glm::vec3{0.0f, 0.0f, 1.0f},
                glm::vec4{u, v, 0.0f, 1.0f},
                glm::vec4{u, v, 0.0f, 1.0f}
            });
            indices.push_back(static_cast<unsigned int>(i));
        }

        return std::make_pair(indices, vertices);
    }

    geometry_data_type generate_circle_geometry_data(float radius, unsigned int segment_count)
    {
        std::vector<unsigned int> indices;
        std::vector<Vertex> vertices;
        for (int i = 0; i < segment_count; ++i) {
            float angle{static_cast<float>(i) / static_cast<float>(segment_count) * 2.0f * static_cast<float>(M_PI)};
            float x{cosf(angle) * radius};
            float y{sinf(angle) * radius};
            float u{x};
            float v{y};
            vertices.push_back(Vertex{
                glm::vec3{x, y, 0.0f},
                glm::vec4{1.0f},
                glm::vec3{0.0f, 0.0f, 1.0f},
                glm::vec4{u, v, 0.0f, 1.0f},
                glm::vec4{u, v, 0.0f, 1.0f}
            });
            indices.push_back(static_cast<unsigned int>(i));
        }

        return std::make_pair(indices, vertices);
    }

    geometry_data_type generate_plane_geometry_data(float width, float height, unsigned int width_segments_count, unsigned int height_segments_count)
    {
        std::vector<unsigned int> indices;
        std::vector<Vertex> vertices;

        float half_height{height * 0.5f};
        float segment_height{height / static_cast<float>(height_segments_count)};

        float half_width{width * 0.5f};
        float segment_width{width / static_cast<float>(width_segments_count)};

        glm::vec3 normal{0.0f, 0.0f, 1.0f};
        for (unsigned int i = 0; i <= height_segments_count; ++i) {
            float y{static_cast<float>(i) * segment_height - half_height};
            float v{static_cast<float>(i) / static_cast<float>(height_segments_count)};

            for (unsigned int j = 0; j <= width_segments_count; ++j) {
                float x{static_cast<float>(j) * segment_width - half_width};
                float u{static_cast<float>(j) / static_cast<float>(width_segments_count)};

                vertices.push_back(Vertex{
                    glm::vec3{x, y, 0.0f},
                    glm::vec4{1.0f},
                    glm::vec3{0.0f, 0.0f, 1.0f},
                    glm::vec4{u, v, 0.0f, 1.0f},
                    glm::vec4{u, v, 0.0f, 1.0f}
                });
            }
        }

        for (unsigned int i = 0; i < height_segments_count; ++i) {
            for (unsigned int j = 0; j < width_segments_count; ++j) {
                unsigned int index_a{i * (width_segments_count + 1) + j};
                unsigned int index_b{index_a + 1};
                unsigned int index_c{index_a + (width_segments_count + 1)};
                unsigned int index_d{index_c + 1};

                indices.push_back(index_c);
                indices.push_back(index_b);
                indices.push_back(index_a);

                indices.push_back(index_c);
                indices.push_back(index_d);
                indices.push_back(index_b);
            }
        }

        return std::make_pair(indices, vertices);
    }

    geometry_data_type
    generate_sphere_geometry_data(float radius, unsigned int segment_count, unsigned int ring_count)
    {
        std::vector<unsigned int> indices;
        std::vector<Vertex> vertices;

        for (unsigned int ring = 0; ring <= ring_count; ++ring) {
            float v{static_cast<float>(ring) / static_cast<float>(ring_count)};
            for (unsigned int segment = 0; segment <= segment_count; ++segment) {
                float u{static_cast<float>(segment) / static_cast<float>(segment_count)};

                float theta{u * static_cast<float>(M_PI) * 2.0f};
                float phi{v * static_cast<float>(M_PI)};

                float cos_theta{cosf(theta)};
                float sin_theta{sinf(theta)};
                float sin_phi{sinf(phi)};
                float cos_phi{cosf(phi)};

                float x{cos_theta * sin_phi};
                float y{cos_phi};
                float z{sin_theta * sin_phi};

                vertices.push_back(Vertex{
                    glm::vec3{x * radius, y * radius, z * radius},
                    glm::vec4{1.0f},
                    glm::vec3{x, y, z},
                    glm::vec4{u, 1.0f - v, 0.0f, 1.0f},
                    glm::vec4{u, 1.0f - v, 0.0f, 1.0f}
                });
            }
        }

        for (unsigned int ring = 0; ring < ring_count; ++ring) {
            for (unsigned int segment = 0; segment < segment_count; ++segment) {
                unsigned int index_a{ring * (segment_count + 1) + segment};
                unsigned int index_b{index_a + (segment_count + 1)};
                unsigned int index_c{index_a + 1};
                unsigned int index_d{index_b + 1};

                indices.push_back(index_a);
                indices.push_back(index_b);
                indices.push_back(index_c);

                indices.push_back(index_b);
                indices.push_back(index_d);
                indices.push_back(index_c);
            }
        }

        return std::make_pair(indices, vertices);
    }
}

#endif
