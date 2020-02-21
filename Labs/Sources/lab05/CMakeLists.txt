cmake_minimum_required(VERSION 3.15)
project(aur)

set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories("./include")
add_executable(aur
    include/scene/scene.hpp
    include/objects/object.hpp
    include/objects/camera.hpp
    include/objects/mesh.hpp
    include/geometries/vertex.hpp
    include/geometries/geometry.hpp
    include/geometries/es2_geometry.hpp
    include/geometries/geometry_generators.hpp
    include/materials/material.hpp
    include/materials/constant_material.hpp
    include/materials/es2_constant_material.hpp
    include/textures/texture.hpp
    include/textures/es2_texture.hpp
    include/renderer/renderer.hpp
    include/renderer/es2_renderer.hpp
    include/renderer/shader.hpp
    include/renderer/es2_shader.hpp
    include/window/window.hpp
    include/window/sdl_window.hpp
    include/utilities/utilities.hpp
    include/aur.hpp
    main.cpp
)
target_link_libraries(aur ${CONAN_LIBS})
