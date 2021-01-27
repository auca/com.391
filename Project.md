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

* <https://github.com/toksaitov/asr-project/tree/bd6ac0455700f285ea0aeccbe7c0f9ca2c816002>

Note that you need to point to a specific commit to get Version 1.0 of the
graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git
git checkout bd6ac0455700f285ea0aeccbe7c0f9ca2c816002
```

### Task 2 (Engine Version 1.0)

Use the first version of the engine from the previous task and add `circle_test.cpp` and
`rectangle_test.cpp` test files to the tests directory. Change the `CMakeLists.txt` build
config to accommodate the new tests. You can copy the `triangle_test.cpp` code into the files
to use as a starter code. Create a structure to represent one vertex of a geometry. Create
functions

```cpp
static std::vector<Vertex> generate_circle_geometry_data(float radius, unsigned int segment_count) { /* ... */ }
```

and

```cpp
static std::vector<Vertex> generate_rectangle_geometry_data(float width, float height, unsigned int width_segments_count, unsigned int height_segments_count) { /* ... */ }
```

Use them in the `main` function at an appropriate place to generate the geometry vertex data
packed into a vector (don't forget to include its header). Allow parameters such as radius,
width, height, and segment count to influence the number of triangles generated to represent
the figure. Commit, push to the private repository (get it from the instructor if you don't
have one). Submit the commit ID to Canvas before the deadline.

## Resources

3D Math Primer for Graphics and Game Development, Second Edition by Fletcher
Done and Ian Parberry

Chapter 3, 4, 5, 6
Chapter 10
