Project Tasks for Engine Version 2.0
====================================

## ASR: Testing

AUCA Simple Renderer (ASR) is a graphics engine being developed in the course Computer Graphics (COM-391) at AUCA to study topics of real-time computer graphics.

In this set of practice tasks, students must develop various test applications to demonstrate the correctness of the **object-oriented** engine's implementation.

### Task 9 (Engine Version 2.0)

Ensure that your development environment is set correctly, and you can compile, run, and debug the following version of the engine

* <https://github.com/toksaitov/asr-project/tree/b96c19c2b95c2fe83289cac091878b2480eab536>

Note that you need to point to a specific commit to get Version 2.0 of the graphics engine.

```bash
git clone https://github.com/toksaitov/asr-project.git asr-2.0
cd asr-2.0
git checkout b96c19c2b95c2fe83289cac091878b2480eab536
```

After updating the engine, remember to recreate the build directory according to the instructions in the engine's Readme file.

If you have trouble building the engine, disable the audio library by removing the line `sdl_mixer/...` from the `conanfile.txt`.

### Task 10, Course Project (Engine Version 2.0)

![Doom-like Game](https://i.imgur.com/nRWcwWN.png)

Build one level of an FPS (First-Person Shooter) game by modifying/improving the `general_usage_test.cpp` in a new file `demo_test.cpp`. The project is open, and we encourage you to be creative. Your game should include at least the following features:

* A player character that can move around the level using the keyboard.
* A level with walls, floors, and ceilings, textured, and shaded.
* Enemies that spawn infinitely and move towards the player character.
* The player should be able to look around using the mouse.
* The player should be able to shoot enemies using the mouse.
* The game should continue until the player character is killed by an enemy.
* The score should be displayed on the screen. You will have to figure out how to do this on your own as our engine does not provide text rendering capabilities.

## Resources

3D Math Primer for Graphics and Game Development, Second Edition by Fletcher Done and Ian Parberry

Chapter 1, 2, 3, 4, 5, 6
Chapter 10
