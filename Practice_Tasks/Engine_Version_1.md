Practice Tasks for Engine Version 1.0
=====================================

## ASR: Testing

AUCA Simple Renderer (ASR) is a graphics engine being developed in the course Computer Graphics (COM-391) at AUCA to study topics of real-time computer graphics.

In this set of practice tasks, students must develop various test applications to demonstrate the correctness of the **procedural** engine's implementation.

### Task 1 (Engine Version 1.0)

![Triangle](https://i.imgur.com/fOPt4OE.png)

Ensure that your development environment is set correctly, and you can compile, run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/2ebd7a0c3f0a79e54a9827bb4bc6f25320f2e3d3>

Note that you must point Git to a specific commit to get Version 1.0 of the graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git
git checkout 2ebd7a0c3f0a79e54a9827bb4bc6f25320f2e3d3
```

### Task 2 (Engine Version 1.0)

![Circle with 100 segments](https://i.imgur.com/cWuwmBI.png)
![Rectangle](https://i.imgur.com/XUcM9EG.png)

Use version 1.0 of the engine from the previous task and add `circle_test.cpp` and `rectangle_test.cpp` test files to the `tests` directory. Change the `CMakeLists.txt` build config to accommodate the new tests. You can copy the `triangle_test.cpp` code into the files to use as a starter code. Create a structure to represent one vertex of a geometry. Create functions

```cpp
std::vector<float> generate_circle_geometry_data(
                       float radius,
                       unsigned int segment_count
                   );
```

and

```cpp
std::vector<float> generate_rectangle_geometry_data(
                       float width,
                       float height,
                       unsigned int width_segments_count,
                       unsigned int height_segments_count
                   );
```

Use them in the `main` function at an appropriate place to generate the geometry vertex data packed into a vector (don't forget to include its header). Allow parameters such as radius, width, height, and segment count to influence the number of triangles generated to represent the figure.

For a circle

* `segment_count` is the number of triangles from which the circle is formed.

For a rectangle

* `width_segments_count` is the number of segmented rectangular faces along the rectangle's width.

* `height_segments_count` is the number of segmented rectangular faces along the rectangle's height.

The vertices of the triangles MUST be specified in the counter-clockwise (CCW) order.

![CW vs CCW](https://www.khronos.org/opengl/wiki_opengl/images/Winding_order.png)

#### Examples

The geometry MUST have the following vertices and triangles for ten segments of a circle.

![Circle with 10 segments](https://i.imgur.com/y0dIDuo.png)
![Mesh of a circle with 10 segments](https://i.imgur.com/JHasEVd.png)

The geometry MUST have the following vertices and triangles for five width and height segments of a rectangle.

![Rectangle with five width and five height segments](https://i.imgur.com/XUcM9EG.png)
![Mesh of a rectangle with five width and five height segments](https://i.imgur.com/AGgiPDB.png)

The mesh on the right is shown for demonstration purposes only. You don't have to draw it. Nevertheless, ensure that your circle and rectangle geometries have the same vertices and triangles. You will get zero otherwise.

Commit and push to the private repository (get it from the instructor if you don't have one). You should send the `circle_test.cpp` and `rectangle_test.cpp` files under the `lab-1` directory. Do not submit any other files. Your grade will be lowered for that. Submit the last commit URL to Canvas before the deadline.

### Task 3 (Engine Version 1.1)

Ensure that your development environment is set correctly, and you can compile,
run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/?>

Note that you need to point to a specific commit to get Version 1.1 of the
graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git
git checkout ?
```

After updating the engine, do not forget to run

```
conan install .. --build missing
```

and

```
cmake ..
```

to download `glm` Math library and to regenerate the project files.

### Task 4 (Engine Version 1.1)

![Triangle](https://i.imgur.com/NLrlhe6.png)
![Sphere](https://i.imgur.com/eTUIFQE.png)
![Box](https://i.imgur.com/UBmVOt2.png)

Use the 1.1 version of the engine from the previous task and add `triangle_test.cpp`
`sphere_test.cpp` and `box_test.cpp` files to the tests directory.  Change the
`CMakeLists.txt` build configuration to accommodate the new tests.

Create functions

```cpp
asr::GeometryPair generate_triangle_geometry_data(
                      asr::GeometryType geometryType,
                      float width,
                      float height,
                      unsigned int width_segments_count,
                      unsigned int height_segments_count
                      glm::vec4 color = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f}
                  );
```

and

```cpp
asr::GeometryPair generate_sphere_geometry_data(
                      asr::GeometryType geometryType,
                      float radius,
                      unsigned int width_segments_count,
                      unsigned int height_segments_count,
                      glm::vec4 color = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f}
                  );
```

and

```cpp
asr::GeometryPair generate_box_geometry_data(
                      asr::GeometryType geometryType,
                      float width,
                      float height,
                      float depth
                      unsigned int width_segments_count,
                      unsigned int height_segments_count,
                      unsigned int depth_segments_count,
                      glm::vec4 color = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f}
                  );
```

Use them in the `main` function at an appropriate place to generate the geometry
vertex and index data packed into a vector (don't forget to include its header).
Allow parameters such as radius, width, height segment count to influence the
number of triangles generated to represent the figure. The vertices of the
triangles MUST be specified in the counter-clockwise (CCW) order. You DO NOT
need to draw edges and vertices.

In both tests, add event handlers to allow control of the camera. The `WASD`
keys must orient the camera (rotate to left/right, up/down). The arrow keys
(`UP`, `DOWN`) must move the camera forward to the current orientation of the
camera. You can use `set_sdl_key_down_event_handler` or
`set_sdl_keys_down_event_handler` functions to setup keyboard event handling
with SDL. Refer to SDL documentation to find the key code constants.

Commit and push to the private repository (get it from the instructor if you don't
have one). You should send the `triangle_test.cpp`, `sphere_test.cpp` and `box_test.cpp` files
placed under the `lab-2` directory. Do not submit any other files. You grade will
be lowered for that. Submit the last commit ID to Canvas before the deadline.

### Task 5 (Engine Version 1.2)

Ensure that your development environment is set correctly, and you can compile,
run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/?>

Note that you need to point to a specific commit to get Version 1.2 of the
graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git
git checkout ?
```

After updating the engine, do not forget to run

```
conan install .. --build missing
```

and

```
cmake ..
```

to download `stb` image loading library and to regenerate the project files.

## Task 6 (Engine Version 1.2)

![Transform 1](https://i.imgur.com/crijcUt.png)
![Transofrm 2](https://i.imgur.com/423Lmbm.png)

Use the 1.2 version of the engine from the previous task and add
`transform1_test.cpp` and `transform2_test.cpp` files to the tests directory.
Change the `CMakeLists.txt` build configuration to accommodate the new tests.

In the `transform1_test.cpp` test, you should create the scene from the first
screenshot. The scene should contain the Sun, Venus, Earth, and Moon represented
with textured spheres. You can find the textures in the `data/images` folder.
All celestial bodies should rotate around their axis at different speeds. The
spheres of Venus and Earth should move around the Sun sphere. The Moon should
rotate around the Earth. The speed of rotation should not depend on the speed of
rendering.

In the `transform2_test.cpp` test, you should create the clocks from the second
screenshot. The clocks should rotate around the `y` axis. The rotation should
not depend on the speed of rendering. It would be best to use the smallest
number of geometry buffers sent to the GPU. The clocks must show the correct
local time of the computer where the program is running.

Commit and push to the private repository (get it from the instructor if you don't
have one). You should send the `transform1_test.cpp`, `transform2_test.cpp` files
placed under the `lab-3` directory. Do not submit any other files. You grade will
be lowered for that. Submit the last commit ID to Canvas before the deadline.

### Task 7 (Engine Version 1.3)

Ensure that your development environment is set correctly, and you can compile,
run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/?>

Note that you need to point to a specific commit to get Version 1.3 of the
graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git
git checkout ?
```

After updating the engine, do not forget to run

```
cmake ..
```

to regenerate the project files.

## Task 8 (Engine Version 1.3)

![Lights](https://i.imgur.com/5PSbN06.png)

Use the 1.3 version of the engine from the previous task and the
`lighting_test.cpp` file in the tests directory. In the `lighting_test.cpp` test,
you should create the scene from the first screenshot. The scene should contain
a plane stretching up to the horizon, a sphere at the center, and (!) two (not one)
point-lights represented by two additional white spheres orbiting around. There
are at least three simple approaches to how you can add a second light. The
challenge of this task is to figure it out on your own. You may have to modify
the shader in this task. Be prepared for that.

Commit and push to the private repository (get it from the instructor if you
don't have one). You should send the `lighting_test.cpp` files placed under the
`lab-4` directory. Do not submit any other files. You grade will be lowered for
that. Submit the last commit ID to Canvas before the deadline.

## Resources

3D Math Primer for Graphics and Game Development, Second Edition by Fletcher
Done and Ian Parberry

Chapter 3, 4, 5, 6
Chapter 10
