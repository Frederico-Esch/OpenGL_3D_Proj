#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
typedef std::string string;

struct Size {
    int Width, Height;
    Size(int width, int height):Width(width), Height(height) {}
    Size(Size& size): Width(size.Width), Height(size.Height) {}
    Size(): Width(0), Height(0) {}
};
