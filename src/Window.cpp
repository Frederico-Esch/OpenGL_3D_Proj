#include <Window.h>

GLFWwindow* Window::getGLFWWindow() { return WindowPtr; }

Size Window::getSize() { return WindowSize; }

void Window::_ResizeCallBack(GLFWwindow* window, int width, int height) {
    Window* _this = (Window*)glfwGetWindowUserPointer(window);

    _this->WindowSize.Width = width;
    _this->WindowSize.Height = height;

    glViewport(0, 0, width, height);
}

Window::Window(int width, int height, string name, GLFWmonitor* monitor, GLFWwindow* parent)
{
    if(!glfwInit()) {
        auto exception = std::runtime_error("GLFW failed to init");
        std::cout << exception.what() << std::endl;
        throw exception;
    }

    WindowSize = Size(width, height);

    auto windowHandler = glfwCreateWindow(width, height, name.c_str(), monitor, parent);
    if ( windowHandler == nullptr) {
        glfwTerminate();
        auto exception = std::runtime_error("Failed to create window");
        std::cout << exception.what() << std::endl;
        throw exception;
    }
    glfwMakeContextCurrent(windowHandler);
    WindowPtr = windowHandler;

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        auto exception = std::runtime_error("GLAD failed to load");
        std::cout << exception.what() << std::endl;
        throw exception;
    }

    glfwSetWindowUserPointer(windowHandler, this);
    glfwSetWindowSizeCallback(windowHandler, Window::_ResizeCallBack);

#ifdef DEBUG_PRINT
    std::cout << "Window Initialized" << std::endl;
    std::cout << "GLFW Context Current Set" << std::endl;
#endif
}

Window::~Window() {
    glfwDestroyWindow(WindowPtr);

#ifdef DEBUG_PRINT
    std::cout << "Window Destroyed" << std::endl;
#endif
}
