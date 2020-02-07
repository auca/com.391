#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "scene.hpp"
#include "window.hpp"

class Renderer {
public:
    virtual ~Renderer() = default;

    virtual void setup(Scene &scene, Window &window) = 0;

    virtual void render(Scene &scene, Window &window) = 0;
};

#endif
