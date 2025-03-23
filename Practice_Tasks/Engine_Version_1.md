Practice Tasks for Engine Version 1.0
=====================================

## ASR: Testing

AUCA Simple Renderer (ASR) is a graphics engine being developed in the course Computer Graphics (COM-391) at AUCA to study topics of real-time computer graphics.

In this set of practice tasks, students must develop various test applications to demonstrate the correctness of the **procedural** engine's implementation.

### Task 1 (Engine Version 1.0)

<img src="https://i.imgur.com/EcfTLqp.png" width="600" alt="Triangle" />

Ensure that your development environment is set correctly, and you can compile, run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/ecdd60a4ed3c483fe7174b3d585ed8033e5ab704>

Note that you must point Git to a specific commit to get Version 1.0 of the graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git asr-1.0
cd asr-1.0
git checkout ecdd60a4ed3c483fe7174b3d585ed8033e5ab704
```

### Task 2 (Engine Version 1.0)

<img src="https://i.imgur.com/94CDSIB.png" width="600" alt="Circle with 100 segments" />
<img src="https://i.imgur.com/Pe2jbhB.png" width="600" alt="Rectangle" />

Use version 1.0 of the engine from the previous task and add `circle_test.cpp` and `rectangle_test.cpp` test files to the `tests` directory. Change the `CMakeLists.txt` build config to accommodate the new tests. You can copy the `triangle_test.cpp` code into the files to use as a starter code. Create functions

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

The wireframe in the second screenshot is provided for demonstration purposes only; you do not need to draw it. However, please ensure that your circle and rectangle geometries share the same vertices and triangles. Consult your instructor on how to verify this. Failure to generate an identical mesh topology will result in a score of zero.

### Task 3 (Engine Version 1.1)

Ensure that your development environment is set correctly, and you can compile, run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/df53458f014ee51400018884ad0e8fa3fa8c4538>

Note that you must point Git to a specific commit to get Version 1.1 of the graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git asr-1.1
cd asr-1.1
git checkout df53458f014ee51400018884ad0e8fa3fa8c4538
```

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

In the `main` function, use these functions appropriately to generate the geometry's vertex and index data, and store them in C++ vectors. Remember to include the `vector` header. Adjust parameters such as radius, width, and the number of height segments to control how many triangles represent the figure. Ensure the triangle vertices are specified in counter-clockwise (CCW) order. Finally, make sure to render both edges and vertices this time.

In the `sphere_test.cpp` and `box_test.cpp` tests, add event handlers for camera control. The `WASD` keys should adjust the camera's orientation (rotate left/right, up/down), and the arrow keys (`UP`, `DOWN`) should move the camera forward in the direction it's facing. Use either the `set_sdl_key_down_event_handler` or `set_sdl_keys_down_event_handler` functions for keyboard event handling with SDL. Consult the SDL documentation for keyboard scan codes.

### Task 5 (Engine Version 1.2)

Ensure that your development environment is set correctly, and you can compile, run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/88870724ed491c986f6049f2c1aea961b118c903>

Note that you must point Git to a specific commit to get Version 1.2 of the graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git asr-1.2
cd asr-1.2
git checkout 88870724ed491c986f6049f2c1aea961b118c903
```

### Task 6 (Engine Version 1.2)

![Transform 1](https://i.imgur.com/crijcUt.png)
![Transofrm 2](https://i.imgur.com/423Lmbm.png)

Use version 1.2 of the engine from the previous task, and add the `transform1_test.cpp` and `transform2_test.cpp` files to the `tests` directory. Update the `CMakeLists.txt` build configuration to include the new tests.

For the `transform1_test.cpp` test, create the scene depicted in the first screenshot. This scene should include textured spheres representing the Sun, Venus, Earth, and Moon, using textures located in the `data/images` folder. Each celestial body should rotate around its axis at a unique speed. Additionally, the spheres for Venus and Earth should orbit the Sun, while the Moon should orbit Earth. Ensure that the rotational speeds remain independent of the rendering speed.

For the `transform2_test.cpp` test, reproduce the clocks shown in the second screenshot. These clocks should rotate around the `y` axis, with their motion independent of the rendering speed. Aim to use the fewest number of geometry buffers possible when sending data to the GPU. The clocks must display the correct local time on the computer where the program is running.

We encourage you to push the boundaries of the provided screenshots by adding your own creative touches to make the programs even more engaging. Consider experimenting with additional objects, visual effects, refined animations, simulations, or enhanced interactivity that complement the core requirements. The best works will be awarded up to two extra points.

## Resources

3D Math Primer for Graphics and Game Development, Second Edition by Fletcher Done and Ian Parberry

* Chapter 1, 2, 3, 4, 5, 6
* Chapter 10
