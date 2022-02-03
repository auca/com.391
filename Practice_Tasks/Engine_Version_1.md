Practice Tasks for Engine Version 1.0
=====================================

## ASR: Testing

AUCA Simple Renderer (ASR) is a graphics engine being developed on the course
Computer Graphics (COM-391) at AUCA to study topics of real-time computer
graphics.

In this set of practice tasks, students have to develop various test
applications to demonstrate the correctness of the **procedural** engine's
implementation.

### Task 1 (Engine Version 1.0)

![Triangle](https://i.imgur.com/fOPt4OE.png)

Ensure that your development environment is set correctly, and you can compile,
run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/267644121a315f242c6136bcd2a8f2554a50775a>

Note that you need to point to a specific commit to get Version 1.0 of the
graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git
git checkout 267644121a315f242c6136bcd2a8f2554a50775a
```

### Task 2 (Engine Version 1.0)

![Circle with 100 segments](https://i.imgur.com/cWuwmBI.png)
![Rectangle](https://i.imgur.com/XUcM9EG.png)

Use the 1.0 version of the engine from the previous task and add
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

## Resources

3D Math Primer for Graphics and Game Development, Second Edition by Fletcher
Done and Ian Parberry

Chapter 3, 4, 5, 6
Chapter 10
