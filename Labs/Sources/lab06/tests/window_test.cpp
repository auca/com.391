#include "aur.hpp"

[[ noreturn ]]
int main(int argc, char **argv)
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur", 0, 0);

    // TODO

    std::vector<std::shared_ptr<Object>> objects { };
    auto scene = std::make_shared<Scene>(objects);

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        // TODO

        renderer.render();
    }
}
