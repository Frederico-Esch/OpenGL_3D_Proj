#pragma once
#include <main.h>
#include <functional>

class Window {
private:
    GLFWwindow *WindowPtr = nullptr;
    Size WindowSize;
    string Name;

    static void _ResizeCallBack(GLFWwindow* window, int width, int height);
public:
    Window(int width, int height, string name, GLFWmonitor* monitor, GLFWwindow* parent);
    ~Window();

    GLFWwindow* getGLFWWindow();
    Size getSize();
};
