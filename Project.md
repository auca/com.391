Course Project
==============

## ASR: Testing

AUCA Simple Renderer (ASR) is a graphics engine being developed on the course
Computer Graphics (COM-391) at AUCA to study topics of real-time computer
graphics.

The task of the course project is to develop many test applications to
demonstrate the correctness of the engine's implementation.

### Task 1 (Engine Version 1.0)

![Triangle](https://i.imgur.com/fOPt4OE.png)

Ensure that your development environment is set correctly, and you can compile,
run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/48ed4628a758fb6fdd3998d2a5b4dbad37606849>

Note that you need to point to a specific commit to get Version 1.0 of the
graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git
git checkout 48ed4628a758fb6fdd3998d2a5b4dbad37606849
```

### Task 2 (Engine Version 1.0)

![Circle with 100 segments](https://i.imgur.com/cWuwmBI.png)
![Rectangle](https://i.imgur.com/XUcM9EG.png)

Use the first version of the engine from the previous task and add
`circle_test.cpp` and `rectangle_test.cpp` test files to the tests directory.
Change the `CMakeLists.txt` build config to accommodate the new tests. You can
copy the `triangle_test.cpp` code into the files to use as a starter code.
Create a structure to represent one vertex of a geometry. Create functions

```cpp
std::vector<Vertex> generate_circle_geometry_data(
                        float radius,
                        unsigned int segment_count
                    );
```

and

```cpp
std::vector<Vertex> generate_rectangle_geometry_data(
                        float width,
                        float height,
                        unsigned int width_segments_count,
                        unsigned int height_segments_count
                    );
```

Use them in the `main` function at an appropriate place to generate the geometry
vertex data packed into a vector (don't forget to include its header). Allow
parameters such as radius, width, height, and segment count to influence the
number of triangles generated to represent the figure.

For a circle

* `segment_count` is a number of triangles from which the circle is formed.

For a rectangle

* `width_segments_count` is a number of segmented rectangular faces along the
   width of the rectangle.

* `height_segments_count` is a number of segmented rectangular faces along the
   height of the rectangle.

The vertices of the triangles MUST be specified in the counter-clockwise (CCW)
order.

![CW vs CCW](https://www.khronos.org/opengl/wiki_opengl/images/Winding_order.png)

#### Examples

For ten segments of a circle, the geometry MUST have the following vertices and
triangles.

![Circle with 10 segments](https://i.imgur.com/y0dIDuo.png)
![Mesh of a circle with 10 segments](https://i.imgur.com/JHasEVd.png)

For five width and height segments of a rectangle, the geometry MUST have the
following vertices and triangles.

![Rectangle with 5 and 5 width and height segments](https://i.imgur.com/XUcM9EG.png)
![Mesh of a rectangle with 5 and 5 width and height segments](https://i.imgur.com/mc2me62.png)

The mesh on the right is shown for demonstration purposes only. You don't have
to draw it. Nevertheless, ensure that your circle and rectangle geometries have
the same vertices and triangles. You will get zero otherwise.

Commit, push to the private repository (get it from the instructor if you don't
have one). Upload ALL the engine sources, not only the modified files. Do not
upload intemidiate and binary files. You grade will be lowered for that. Submit
the last commit ID to Canvas before the deadline.

### Task 3 (Engine Version 2.0)

Ensure that your development environment is set correctly, and you can compile,
run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/6534c8ce3db4654663cfdc8ca51d7ea38264b557>

Note that you need to point to a specific commit to get Version 2.0 of the
graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git
git checkout 6534c8ce3db4654663cfdc8ca51d7ea38264b557
```

After updating the engine, do not forget to run

```
conan install ..
```

and

```
cmake ..
```

to download `glm` Math library and to regenerate the project files.

### Task 4 (Engine Version 2.0)

![Sphere](https://i.imgur.com/eTUIFQE.png)
![Box](https://i.imgur.com/UBmVOt2.png)

Use the second version of the engine from the previous task and add
`sphere_test.cpp` and `box_test.cpp` files to the tests directory.  Change the
`CMakeLists.txt` build configuration to accommodate the new tests.

Create functions

```cpp
 std::pair<std::vector<asr::Vertex>, std::vector<unsigned int>>
   generate_sphere_geometry_data(
      float radius,
      unsigned int width_segments_count,
      unsigned int height_segments_count
   );
```

and

```cpp
 std::pair<std::vector<asr::Vertex>, std::vector<unsigned int>>
   generate_box_geometry_data(
      float width,
      float height,
      float depth
      unsigned int width_segments_count,
      unsigned int height_segments_count,
      unsigned int depth_segments_count
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
camera. You can use `set_es2_sdl_key_down_event_handler` or
`set_es2_sdl_keys_down_event_handler` functions to setup keyboard event handling
with SDL. Refer to SDL documentation to find the key code constants.

Commit, push to the private repository (get it from the instructor if you don't
have one). Upload ALL the engine sources, not only the modified files. Do not
upload intemidiate and binary files. You grade will be lowered for that. Submit
the last commit ID to Canvas before the deadline.

### Task 5 (Engine Version 3.0)

Ensure that your development environment is set correctly, and you can compile,
run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/ecd715fe892d5a9b7eda211c8d7b1dd939376b23>

Note that you need to point to a specific commit to get Version 3.0 of the
graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git
git checkout ecd715fe892d5a9b7eda211c8d7b1dd939376b23
```

After updating the engine, do not forget to run

```
conan install ..
```

and

```
cmake ..
```

to download `stb` image loading library and to regenerate the project files. 

## Task 6 (Engine Version 3.0)

![Transform 1](https://i.imgur.com/crijcUt.png)
![Transofrm 2](https://i.imgur.com/423Lmbm.png)

Use the third version of the engine from the previous task and add
`transform1_test.cpp` and `transform2_test.cpp` files to the tests directory.
Change the `CMakeLists.txt` build configuration to accommodate the new tests.

In the `transform1_test.cpp` test, you should create the scene from the first
screenshot. The scene should contain the Sun, Venus, Earth, and Moon represente
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

Commit, push to the private repository (get it from the instructor if you don't
have one). Upload ALL the engine sources, not only the modified files. Do not
upload intemidiate and binary files. You grade will be lowered for that. Submit
the last commit ID to Canvas before the deadline.

### Task 7 (Engine Version 4.0)

Ensure that your development environment is set correctly, and you can compile,
run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/eadd1c40994fa6d9e51f2282d10030ccf452c21f>

Note that you need to point to a specific commit to get Version 4.0 of the
graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git
git checkout eadd1c40994fa6d9e51f2282d10030ccf452c21f
```

After updating the engine, do not forget to run

```
cmake ..
```

to regenerate the project files.

## Task 8 (Engine Version 4.0)

![Lights](https://i.imgur.com/5PSbN06.png)

Use the fourth version of the engine from the previous task and add
`lighting_test.cpp` file to the tests directory. Change the `CMakeLists.txt`
build configuration to accommodate the new test.

In the `lighting_test.cpp` test, you should create the scene from the first
screenshot. The scene should contain a plane stretching up to the horizon, a
sphere at the center, and two point-lights represented by two additional white
spheres orbiting around. There are at least three simple approaches to how you
can add a second light. The challenge of this task is to figure it out on your
own.

You can find the shader for one light [here](https://gist.github.com/toksaitov/41ccaaad7ea513f3240de80cd147d053).

Commit, push to the private repository (get it from the instructor if you don't
have one). Upload ALL the engine sources, not only the modified files. Do not
upload intemidiate and binary files. You grade will be lowered for that. Submit
the last commit ID to Canvas before the deadline.

### Task 9 (Engine Version 5.0)

Ensure that your development environment is set correctly, and you can compile,
run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/8db682dabd766058febe41ac784ef56dc381b201>

Note that you need to point to a specific commit to get Version 5.0 of the
graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git
git checkout 8db682dabd766058febe41ac784ef56dc381b201
```

After updating the engine, do not forget to run

```
cmake ..
```

to download `imgui` library and to regenerate the project files. 

## Task 10 (Engine Version 5.0)

![Sprites](https://i.imgur.com/nRWcwWN.png)

Use the fifth version of the engine from the previous task and add
`game_test.cpp` file to the tests directory. Change the `CMakeLists.txt`
build configuration to accommodate the new test.

In the `game_test.cpp` test, you should create one level of any classic 2.5D
shooter game (like Doom).

Your level should include at least the following:

* Create one level (at least one rectangular room with textured ground and walls).
* Add at least one enemy type (the enemy should be a plane with texture-based sprite animation, enemies can move).
* Add the first-person player (the player should be the camera and an overlay mesh with texture-based sprite animation).
* Add any basic game logic (shooting, destroying enemies with ray intersection testing, etc...). You can use
  overlays to add 'You won!' / 'You lost!', 'Menu' screens.

Note that any extra effort may be awarded with a small number of extra points.
Be creative.

You may find the following test files usefull:

* `general_usage_test.cpp`
* `box_test.cpp`
* `normal_mapping_test.cpp`

Commit, push to the private repository (get it from the instructor if you don't
have one). Upload ALL the engine sources, not only the modified files. Do not
upload intemidiate and binary files. You grade will be lowered for that. Submit
the last commit ID to Canvas before the deadline.

## Resources

3D Math Primer for Graphics and Game Development, Second Edition by Fletcher
Done and Ian Parberry

Chapter 3, 4, 5, 6
Chapter 10
