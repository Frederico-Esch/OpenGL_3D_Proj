#pragma once
#include <main.h>

class Window {
private:
    GLFWwindow *WindowPtr = nullptr;
    Size WindowSize;
    string Name;

public:
    Window(int width, int height, string name, GLFWmonitor* monitor, GLFWwindow* parent);
    ~Window();

    GLFWwindow* getGLFWWindow();
    Size getSize();
};
