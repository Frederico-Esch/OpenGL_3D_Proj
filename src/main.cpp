#include <main.h>
#include <Window.h>
#include <Renderer.h>

int main()
{

    Window window(800, 600, "Main Window", nullptr, nullptr);
    Renderer renderer(window);
    glClearColor(0.5f, 0.2f, 0.7f, 1.f);

    renderer.Run();

    return 0;
}
