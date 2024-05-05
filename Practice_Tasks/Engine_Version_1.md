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

<img src="https://i.imgur.com/94CDSIB.png" width="600" alt="Circle with 100 segments" />
<img src="https://i.imgur.com/Pe2jbhB.png" width="600" alt="Rectangle" />

Use version 1.0 of the engine from the previous task and add `circle_test.cpp` and `rectangle_test.cpp` test files to the `tests` directory. Change the `CMakeLists.txt` build config to accommodate the new tests. You can copy the `triangle_test.cpp` code into the files to use as a starter code. Create a structure to represent one vertex of a geometry. Create functions

```cpp
std::vector<float> generate_circle_geometry_data(
    float radius,
    unsigned int segments
);
```

and

```cpp
std::vector<float> generate_rectangle_geometry_data(
    float width,
    float height,
    unsigned int width_segments,
    unsigned int height_segments
);
```

Use them in the `main` function at an appropriate place to generate the geometry vertex data packed into a vector (don't forget to include its header). Allow parameters such as radius, width, height, and segment count to influence the number of triangles generated to represent the figure.

For a circle

* `segments` is the number of triangles from which the circle is formed.

For a rectangle

* `width_segments` is the number of segmented rectangular faces along the rectangle's width.

* `height_segments` is the number of segmented rectangular faces along the rectangle's height.

The vertices of the triangles MUST be specified in the counter-clockwise (CCW) order.

![CW vs CCW](https://www.khronos.org/opengl/wiki_opengl/images/Winding_order.png)

#### Examples

The geometry MUST have the following vertices and triangles for ten segments of a circle.

<img src="https://i.imgur.com/mVgYF9K.png" width="600" alt="Circle with 10 segments" />
<img src="https://i.imgur.com/cRnni7i.png" width="600" alt="Mesh of a circle with 10 segments" />

The geometry MUST have the following vertices and triangles for five width and height segments of a rectangle.

<img src="https://i.imgur.com/Pe2jbhB.png" width="600" alt="Rectangle with five width and five height segments" />
<img src="https://i.imgur.com/GRugyTe.png" width="600" alt="Mesh of a rectangle with five width and five height segments" />

The mesh on the right is shown for demonstration purposes only; you do NOT need to draw it. However, ensure that your circle and rectangle geometries share the same vertices and triangles. Consult your instructor on how to verify this. Failure to do so will result in a score of zero.

### Task 3 (Engine Version 1.1)

Ensure that your development environment is set correctly, and you can compile, run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/5980e337f0f23c35d43d9bd7e1232eb95ccfbaf9>

Note that you need to point to a specific commit to get Version 1.1 of the graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git asr-1.1
cd asr-1.1
git checkout 5980e337f0f23c35d43d9bd7e1232eb95ccfbaf9
```

After updating the engine, remember to recreate the build directory according to the instructions in the engine's Readme file.

### Task 4 (Engine Version 1.1)

<img src="https://i.imgur.com/NLrlhe6.png" width="600" alt="Triangle" />

<img src="https://i.imgur.com/qgrnRVF.png" width="600" alt="Sphere" />

<img src="https://i.imgur.com/ZLteynk.png" width="600" alt="Box" />

Use version 1.1 of the engine from the previous task and add the `triangle_test.cpp`, `sphere_test.cpp`, and `box_test.cpp` files to the tests directory. Update the `CMakeLists.txt` build configuration to include the new tests.

Create the following functions:

```cpp
asr::GeometryPair generate_triangle_geometry_data(
    asr::GeometryType geometry_type,
    float width,
    float height,
    unsigned int segments,
    glm::vec4 color = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f}
);
```

```cpp
asr::GeometryPair generate_sphere_geometry_data(
    asr::GeometryType geometry_type,
    float radius,
    unsigned int width_segments,
    unsigned int height_segments,
    glm::vec4 color = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f}
);
```

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

In the `main` function, use these functions appropriately to generate the geometry's vertex and index data, packing them into C++ vector containers. Remember to include the `vector` header. Adjust parameters such as radius, width, and height segment count to influence the number of triangles representing the figure. Ensure the vertices of the triangles are specified in counter-clockwise (CCW) order. You must also render edges and vertices.

In the `sphere_test.cpp` and `box_test.cpp` tests, add event handlers for camera control. The `WASD` keys should adjust the camera's orientation (rotate left/right, up/down), and the arrow keys (`UP`, `DOWN`) should move the camera forward in the direction it's facing. Use either the `set_sdl_key_down_event_handler` or `set_sdl_keys_down_event_handler` functions for keyboard event handling with SDL. Consult the SDL documentation for keyboard scan codes.

### Task 5 (Engine Version 1.2)

Ensure that your development environment is set correctly, and you can compile, run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/aff15ae15ecbd8afd93e393d0b5200a37b10a1b7>

Note that you need to point to a specific commit to get Version 1.2 of the graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git asr-1.2
cd asr-1.2
git checkout aff15ae15ecbd8afd93e393d0b5200a37b10a1b7
```

After updating the engine, remember to recreate the build directory according to the instructions in the engine's Readme file.

### Task 6 (Engine Version 1.2)

![Transform 1](https://i.imgur.com/crijcUt.png)
![Transofrm 2](https://i.imgur.com/423Lmbm.png)

Use version 1.2 of the engine from the previous task and add the `transform1_test.cpp` and `transform2_test.cpp` files to the tests directory. Modify the `CMakeLists.txt` build configuration to include these new tests.

In the `transform1_test.cpp` test, create the scene depicted in the first screenshot. This scene should contain textured spheres representing the Sun, Venus, Earth, and Moon, with textures found in the `data/images` folder. Each celestial body should rotate around its axis at a unique speed. Additionally, the spheres for Venus and Earth should orbit the Sun, while the Moon orbits Earth. Ensure the rotational speeds are independent of the rendering speed.

In the `transform2_test.cpp` test, reproduce the clocks shown in the second screenshot. These clocks should rotate around the `y` axis, with their motion being independent of the rendering speed. Aim to use the fewest geometry buffers possible when sending data to the GPU. The clocks must display the correct local time of the computer where the program is running.

### Task 7 (Engine Version 1.3)

Ensure that your development environment is set correctly, and you can compile, run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/0b5baccccc469f528d94981cbf23de76d08d089f>

Note that you need to point to a specific commit to get Version 1.3 of the graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git asr-1.3
cd asr-1.3
git checkout 0b5baccccc469f528d94981cbf23de76d08d089f
```

After updating the engine, remember to recreate the build directory according to the instructions in the engine's Readme file.

### Task 8 (Engine Version 1.3)

![Lights](https://i.imgur.com/5PSbN06.png)

Use version 1.3 of the engine from the previous task along with the `lighting_test.cpp` file located in the tests directory. In the `lighting_test.cpp` test, create the scene depicted in the screenshot above. This scene should include a plane extending to the horizon, a central sphere, and two point lights (NOT just one), represented by two white spheres orbiting around the central sphere.

There are at least three approaches to adding a second light. The challenge is to determine the best method independently. What is considered the best is up to you. It may be the best method from the standpoint of code complexity (i.e., duplicating variables and statements responsible for rendering a light), it may be from the standpoint of versatility (allowing more than two lights by using arrays and loops), or perhaps the best from the standpoint of performance. You may need to modify the shader for this task, so be prepared for that. You can find a link to the GLSL language reference at the bottom.

## Resources

3D Math Primer for Graphics and Game Development, Second Edition by Fletcher Done and Ian Parberry

* Chapter 1, 2, 3, 4, 5, 6
* Chapter 10
