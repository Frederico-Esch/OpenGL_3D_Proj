#pragma once
#include <main.h>
#include <Window.h>
#include <Buffers.h>

class Renderer {
private:
    Window* MainWindow = nullptr;
    Buffers* MainBuffers = nullptr;
public:
    Renderer(Window* window, Buffers* buffers);
    Renderer();

    void SetupBlending();
    void Run();
};
