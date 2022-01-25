Practice Tasks for Engine Version 2.0
=====================================

## ASR: Testing

AUCA Simple Renderer (ASR) is a graphics engine being developed on the course
Computer Graphics (COM-391) at AUCA to study topics of real-time computer
graphics.

In this set of practice tasks, students have to develop various test
applications to demonstrate the correctness of the **object-oriented** engine's
implementation.

### Task 1 (Engine Version 2.0)

Ensure that your development environment is set correctly, and you can compile,
run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/8db682dabd766058febe41ac784ef56dc381b201>

Note that you need to point to a specific commit to get Version 2.0 of the
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

## Task 2 (Engine Version 2.0)

Port all the tests from the procedural version of the engine to the new
object-oriented version that you have compiled in the previous task.

Commit, push to the private repository (get it from the instructor if you don't
have one). Upload ALL the engine sources, not only the modified files. Do not
upload intemidiate and binary files. You grade will be lowered for that. Submit
the last commit ID to Canvas before the deadline.

## Task 3 (Engine Version 2.0)

![Sprites](https://i.imgur.com/nRWcwWN.png)

Use the 2.0 version of the engine from the previous task and add
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
