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
