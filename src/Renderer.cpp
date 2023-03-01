#include <Renderer.h>

Renderer::Renderer() { }

Renderer::Renderer(Window window) : MainWindow(window) { }

void Renderer::Run() {
    while (!glfwWindowShouldClose(MainWindow.getGLFWWindow())) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(MainWindow.getGLFWWindow());
        glfwPollEvents();
    }
}
