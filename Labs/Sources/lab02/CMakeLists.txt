cmake_minimum_required(VERSION "2.8.0")

project("lab02")

add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(lab02 lab02.cpp)
target_link_libraries(lab02 ${CONAN_LIBS})

