#include <Renderer.h>

Renderer::Renderer() { }

Renderer::Renderer(Window* window, Buffers* buffers) : MainWindow(window), MainBuffers(buffers) {

#ifdef DEBUG_PRINT
    std::cout << "Renderer Finished Initializing" << std::endl;
#endif
}

void Renderer::Run() {
    if (MainBuffers == nullptr || MainWindow == nullptr) return;

    while (!glfwWindowShouldClose(MainWindow->getGLFWWindow())) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        MainBuffers->Draw();

        glfwSwapBuffers(MainWindow->getGLFWWindow());
        glfwPollEvents();
    }
}
