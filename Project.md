Course Project
=============

## AUR: Testing

AUCA Renderer (AUR) is a graphics engine being developed on the course Computer
Graphics (COM-391) at AUCA to study topics of real-time computer graphics.

The task of the course project is to develop many test applications to
demonstrate the correctness of the engine's implementation.

## Prerequisites

* GCC or Clang to compile
* Conan to download dependencies
* CMake to create build files
* Any IDE (Microsoft Visual Studio or Xcode) to help with development and
  debugging tasks

## Compilation

1. Go to a particular lab version of the engine's directory.
2. Create a `build` directory.

```bash
mkdir build
cd build
```

3. Download dependencies with the Conan package manager.

```bash
conan install ..
```

4. Create build files for your IDE or build system.

```bash
# On Windows for Visual Studio
cmake .. -G "Visual Studio 16 Win64"

# On MacOS for Xcode
cmake .. -G "Xcode"

# On MacOS or Linux to generate Make files
cmake .. -G "Unix Makefiles"
```

5. Run the build scripts or open the IDE to build and run the code. Ensure
   that the `data` directory is available in the current working directory for
   the code to be able to find shaders and textures.

## Tests

In this work you need to write the following tests

1. Window Test:

The test must open the window with an empty scene in fullscreen mode.

![Window Test](https://i.imgur.com/IDPIjPV.png)

2. Triangle Test:

The test must show a triangle at the center of the screen. You have to figure
out on your own, what do you need to do to change the colors of the three
vertices.

![Triangle Test](https://i.imgur.com/JVS5uLN.png)

3. Other Geometries Test:

The test must display a 3 by 3 grid of all the geometries that the utility
classes of the engine can generate. Try to use different parameters to build
variations of the same geometric object.

![Other Geometries Test](https://i.imgur.com/4ID3nAs.png)

4. Scene Graph

Display the clocks similar to the example below. You have to use parenting
to properly rotate the clock hands.

![Scene Graph](https://i.imgur.com/77sqQP4.png)

5. Lighting Test

Display a plane and a sphere with Phong materials applied to them. Add two
point lights moving around the scene to test the lighting subsystem of the
engine.

![Lighting Test](https://i.imgur.com/FKl3ZAS.png)

6. Textured Plane Test

Be able to compile and answer questions about textures.

7. Material Properties Test

Be able to compile and answer questions about material properties (depth testing, culling, blending, fog).

8. Normal Maps (Bump Mapping) Test

Add normal map support to the engine.

9. General Usage Test (Final Project)

* Create one level (at least one rectangular room with textured ground and walls).
* Add at least one enemy type (the enemy should be a plane with texture-based sprite animation, enemies can move).
* Add the first-person player (the player should be the camera and an overlay mesh with texture-based sprite animation).
* Add the basic game logic (shooting, destroying enemies with ray intersection testing).

## Modifying the Build System

For all your tests you need to add the following lines to the build script:

```bash
# ...
add_executable(window_test ${AUR_SOURCES} tests/window_test.cpp)
add_executable(triangle_test ${AUR_SOURCES} tests/triangle_test.cpp)
add_executable(other_geometries_test ${AUR_SOURCES} tests/other_geometries_test.cpp)
add_executable(scene_graph_test ${AUR_SOURCES} tests/scene_graph_test.cpp)
add_executable(lighting_test ${AUR_SOURCES} tests/lighting_test.cpp)

target_link_libraries(window_test ${CONAN_LIBS})
target_link_libraries(triangle_test ${CONAN_LIBS})
target_link_libraries(other_geometries_test ${CONAN_LIBS})
target_link_libraries(scene_graph_test ${CONAN_LIBS})
target_link_libraries(lighting_test ${CONAN_LIBS})
```

## Resources

3D Math Primer for Graphics and Game Development, Second Edition by Fletcher
Done and Ian Parberry

Chapter 3, 4, 5, 6
Chapter 10
