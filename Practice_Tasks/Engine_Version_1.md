Practice Tasks for Engine Version 1.0
=====================================

## ASR: Testing

AUCA Simple Renderer (ASR) is a graphics engine being developed in the course Computer Graphics (COM-391) at AUCA to study topics of real-time computer graphics.

In this set of practice tasks, students must develop various test applications to demonstrate the correctness of the **procedural** engine's implementation.

### Task 1 (Engine Version 1.0)

<img src="https://i.imgur.com/EcfTLqp.png" width="600" alt="Triangle" />

Ensure that your development environment is set correctly, and you can compile, run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/6c7db14f1a2bab226e3aa7057d4974d1d9ed1422>

Note that you must point Git to a specific commit to get Version 1.0 of the graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git asr-1.0
cd asr-1.0
git checkout 6c7db14f1a2bab226e3aa7057d4974d1d9ed1422
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

## Resources

3D Math Primer for Graphics and Game Development, Second Edition by Fletcher Done and Ian Parberry

Chapter 3, 4, 5, 6
Chapter 10
