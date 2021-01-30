Course Project
==============

## ASR: Testing

AUCA Simple Renderer (ASR) is a graphics engine being developed on the course
Computer Graphics (COM-391) at AUCA to study topics of real-time computer
graphics.

The task of the course project is to develop many test applications to
demonstrate the correctness of the engine's implementation.

### Task 1 (Engine Version 1.0)

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

![Circle with 100 segments](https://i.imgur.com/PUOqJhH.png)
![Rectangle](https://i.imgur.com/YN8audT.png)

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

Use them in the `main` function at an appropriate place to generate the geometry vertex data
packed into a vector (don't forget to include its header). Allow parameters such as radius,
width, height, and segment count to influence the number of triangles generated to represent
the figure.

For a circle

* `segment_count` is a number of triangles from which the circle is formed.

For a rectangle

* `width_segments_count` is a number of segmented rectangular faces along the width of the rectangle.
* `height_segments_count` is a number of segmented rectangular faces along the height of the rectangle.

The vertices of the triangles MUST be specified in the counter-clockwise (CCW)
order.

![CW vs CCW](https://www.khronos.org/opengl/wiki_opengl/images/Winding_order.png)

For 10 segments of a circle, the geometry must have the following vertices and
triangles.

![Mesh of a circle with 10 segments](https://i.imgur.com/iAnkr8w.png)
![Circle with 10 segments](https://i.imgur.com/a5DfMTn.png)

For 5 and 5 width and hegith segments of a rectangle, the geometry must have the following vertices and triangles.

![Mesh of a rectangle with 5 and 5 width and height segments](https://i.imgur.com/Yfuu7vF.png)
![Rectangle with 5 and 5 width and height segments](https://i.imgur.com/YN8audT.png)

Vertices and triangles are shown for demonstration purposes. You don't have
to draw them, but you mesh must have the same vertices and triangles. You will
not get points otherwise.

Commit, push to the private repository (get it from the instructor if you don't
have one). Submit the commit ID to Canvas before the deadline.

#### Examples

The test programs should generate similar output.

* [circle_test.cpp](https://i.imgur.com/dzSIxbu.png)
* [rectangle_test.cpp](https://i.imgur.com/91NnNoO.png)

## Resources

3D Math Primer for Graphics and Game Development, Second Edition by Fletcher
Done and Ian Parberry

Chapter 3, 4, 5, 6
Chapter 10
