#pragma once
#include <main.h>
#include <Window.h>

class Renderer {
private:
    Window MainWindow;
public:
    Renderer(Window window);
    Renderer();

    void Run();
};
