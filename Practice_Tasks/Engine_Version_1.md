Practice Tasks for Engine Version 1.0
=====================================

## ASR: Testing

AUCA Simple Renderer (ASR) is a graphics engine being developed in the course Computer Graphics (COM-391) at AUCA to study topics of real-time computer graphics.

In this set of practice tasks, students must develop various test applications to demonstrate the correctness of the **procedural** engine's implementation.

### Task 1 (Engine Version 1.0)

<img src="https://i.imgur.com/EcfTLqp.png" width="600" alt="Triangle" />

Ensure that your development environment is set correctly, and you can compile, run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/46cf65a6f14c207977851b731f5d177fd3379624>

Note that you must point Git to a specific commit to get Version 1.0 of the graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git asr-1.0
cd asr-1.0
git checkout 46cf65a6f14c207977851b731f5d177fd3379624
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

### Task 3 (Engine Version 1.1)

Ensure that your development environment is set correctly, and you can compile, run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/5980e337f0f23c35d43d9bd7e1232eb95ccfbaf9>

Note that you need to point to a specific commit to get Version 1.1 of the graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git asr-1.1
git checkout 5980e337f0f23c35d43d9bd7e1232eb95ccfbaf9
```

After updating the engine, remember to recreate the build directory by following the engine's Readme file.

### Task 4 (Engine Version 1.1)

![Triangle](https://i.imgur.com/NLrlhe6.png)
![Sphere](https://i.imgur.com/eTUIFQE.png)
![Box](https://i.imgur.com/UBmVOt2.png)

Use the previous task's 1.1 version of the engine and add `triangle_test.cpp`, `sphere_test.cpp`, and `box_test.cpp` files to the tests directory. Change the `CMakeLists.txt` build configuration to accommodate the new tests.

Create functions

```cpp
asr::GeometryPair generate_triangle_geometry_data(
                      asr::GeometryType geometry_type,
                      float width,
                      float height,
                      unsigned int segments,
                      glm::vec4 color = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f}
                  );
```

and

```cpp
asr::GeometryPair generate_sphere_geometry_data(
                      asr::GeometryType geometry_type,
                      float radius,
                      unsigned int width_segments,
                      unsigned int height_segments,
                      glm::vec4 color = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f}
                  );
```

and

```cpp
asr::GeometryPair generate_box_geometry_data(
                      asr::GeometryType geometry_type,
                      float width,
                      float height,
                      float depth,
                      unsigned int width_segments,
                      unsigned int height_segments,
                      unsigned int depth_segments,
                      glm::vec4 color = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f}
                  );
```

Use them in the `main` function at an appropriate place to generate the geometry vertex and index data packed into C++ vector containers (don't forget to include the `vector` header). Allow parameters such as radius, width, and height segment count to influence the number of triangles generated to represent the figure. The vertices of the triangles MUST be specified in the counter-clockwise (CCW) order. You MUST draw edges and vertices, too.

In the `sphere_test.cpp` and `box_test.cpp` tests, add event handlers to allow control of the camera. The `WASD` keys must orient the camera (rotate to left/right, up/down). The arrow keys (`UP`, `DOWN`) must move the camera forward to the current orientation of the camera. You can use the `set_sdl_key_down_event_handler` or `set_sdl_keys_down_event_handler` functions to set up keyboard event handling with SDL. Refer to SDL documentation to find the scan codes of the keyboard.

## Resources

3D Math Primer for Graphics and Game Development, Second Edition by Fletcher Done and Ian Parberry

Chapter 3, 4, 5, 6
Chapter 10
