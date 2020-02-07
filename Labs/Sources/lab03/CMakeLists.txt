cmake_minimum_required(VERSION 3.15)
project(lab03)

set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(lab03 lab03.cpp object.hpp geometry.hpp camera.hpp scene.hpp renderer.hpp shader.hpp es2_shader.hpp es2_renderer.hpp window.hpp sdl_window.hpp utilities.hpp material.hpp es2_constant_material.hpp mesh.hpp es2_geometry.hpp)
target_link_libraries(lab03 ${CONAN_LIBS})