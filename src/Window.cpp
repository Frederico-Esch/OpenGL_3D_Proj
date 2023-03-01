#include <Window.h>

Window::Window(){ initilized = false; };

GLFWwindow* Window::getGLFWWindow() { return WindowPtr; }

Size Window::getSize() { return WindowSize; }

Window::Window(int width, int height, string name, GLFWmonitor* monitor, GLFWwindow* parent)
{
    initilized = true;
    if(!glfwInit()) {
        auto exception = new std::exception("GLFW failed to init");
        std::cout << exception->what() << std::endl;
        throw exception;
    }

    WindowSize = Size(width, height);

    auto windowHandler = glfwCreateWindow(width, height, name.c_str(), monitor, parent);
    if ( windowHandler == nullptr) {
        glfwTerminate();
        auto exception = new std::exception("Failed to create window");
        std::cout << exception->what() << std::endl;
        throw exception;
    }
    glfwMakeContextCurrent(windowHandler);
    WindowPtr = windowHandler;

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        auto exception = new std::exception("GLAD failed to load");
        std::cout << exception->what() << std::endl;
        throw exception;
    }
}
