Project Tasks for Engine Version 2.0
====================================

## ASR: Testing

AUCA Simple Renderer (ASR) is a graphics engine developed in the course Computer Graphics (COM-391) at AUCA to study topics related to real-time computer graphics.

In this set of practice tasks, students are required to develop various test applications to demonstrate the correctness of the **object-oriented** engine's implementation.

### Task 9 (Engine Version 2.0)

Ensure that your development environment is set correctly, and you can compile, run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/b05ebb9cfd93a442e0745524f2bb81eff525f2c9>

Note that you need to point to a specific commit to get Version 2.0 of the graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git asr-2.0
cd asr-2.0
git checkout b05ebb9cfd93a442e0745524f2bb81eff525f2c9
```

After updating the engine, remember to recreate the build directory according to the instructions in the engine's Readme file.

If you have trouble building the engine, disable the audio library by removing the line `sdl_mixer/...` from the `conanfile.txt`.

### Task 10, Course Project (Engine Version 2.0)

![Doom-like Game](https://i.imgur.com/nRWcwWN.png)

Build an FPS-style game (First-Person Shooter) with at least one level by creating a new file called `game_test.cpp`. Use the code from `general_usage_test.cpp` as your starting point. The project is open-ended, and we encourage you to be creative. Your game should include, at a minimum, the following features:

* A player character that can move around the level using the keyboard.
* A level featuring textured and shaded walls, floors, and ceilings.
* Enemies that continuously spawn and move toward the player character.
* The ability for the player to look around using the mouse.
* The ability for the player to shoot enemies using the mouse.
* Gameplay that continues until the player character is killed by an enemy.
* A score displayed on the screen. (Note: our engine does not provide text rendering capabilities, so you will need to determine your own solution for this.)

You are allowed to modify the engine itself, as it is missing some quality-of-life features, such as simple access to the `dt` value (timing between frames) to keep animations consistent. Removing objects from the scene graph may also be a challenge. You can modify any class or function, and you can even change the shader code. You are also free to add your own assets—just make sure to place them in the `data` directory. Keep in mind that GitHub may have issues with large binary files.

Ensure you create the window for your game using the code `std::make_shared<ES2SDLWindow>("asr 2.0", 1280, 720)` to enable the grader to take a correct screenshot.

## Resources

3D Math Primer for Graphics and Game Development, Second Edition by Fletcher Done and Ian Parberry

* Chapter 1, 2, 3, 4, 5, 6
* Chapter 10
