Project Tasks for Engine Version 2.0
====================================

## ASR: Testing

AUCA Simple Renderer (ASR) is a graphics engine being developed on the course Computer Graphics (COM-391) at AUCA to study topics of real-time computer graphics.

In this set of practice tasks, students have to develop test applications to demonstrate the correctness of the **object-oriented** engine's implementation.

### Task 9 (Engine Version 2.0)

Ensure that your development environment is set correctly, and you can compile, run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/84a76d927919796e0d4b7a2a6f8f1845c92236ef>

Note that you need to point to a specific commit to get Version 2.0 of the graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git
git checkout 84a76d927919796e0d4b7a2a6f8f1845c92236ef
```

After updating the engine, do not forget to run

```
conan install .. --build missing
```

and

```
cmake ..
```

to download `imgui` and `sdl_mixer` libraries and to regenerate the project files.

If you have trouble building the engine, disable the Audio library by removing the line `sdl_mixer/2.0.4` from the `conanfile.txt`.

### Task 10, Bonus (Engine Version 2.0)

![Sprites](https://i.imgur.com/nRWcwWN.png)

You have two options for this bonus task:

1. Build one level of an FPS (First-Person Shooter) game by modifying/improving the `general_usage_test.cpp` in a new file `demo_test.cpp`.
2. Build a small demo in `demo_test.cpp` inspired by the [Demoscene](https://en.wikipedia.org/wiki/Demoscene) subculture. You can find a lot of examples on [YouTube](https://www.youtube.com/results?search_query=demoscene).

The projects are open, and we encourage you to be creative here. Your task is to impress TAs and instructors to get up to 5 bonus points. Refer to the notes of the last class for specific recommendations.

Commit and push to the private repository (get it from the instructor if you don't have one). You should send the `game_test.cpp` for option one or `demo_test.cpp` for option two. Place one file under the `project` directory. Do not submit any other files. Your grade will be lowered for that. Submit the last commit ID to Canvas before the deadline.

## Resources

3D Math Primer for Graphics and Game Development, Second Edition by Fletcher Done and Ian Parberry

Chapter 3, 4, 5, 6
Chapter 10
