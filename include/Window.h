#pragma once
#include <main.h>

class Window {
private:
  GLFWwindow *WindowPtr;
  Size WindowSize;
  string Name;
  bool initilized;

public:
  Window(int width, int height, string name, GLFWmonitor* monitor, GLFWwindow* parent);
  Window();

  GLFWwindow* getGLFWWindow();
  Size getSize();
};
