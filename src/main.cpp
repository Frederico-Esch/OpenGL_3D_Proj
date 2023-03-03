#include <main.h>
#include <Window.h>
#include <Renderer.h>

int main()
{

    Window window(800, 600, "Main Window", nullptr, nullptr);
    Buffers buffers;

    std::vector<float> vertexes {
        -.5f, -.5f, 0.f,
         .5f, -.5f, 0.f,
         0.f,  0.f, 0.f,

        -.5f,  .5f, 0.f,
         .5f,  .5f, 0.f,
         0.f,  0.f, 0.f,
    };

    std::vector<unsigned int> elements { 0, 1, 2, 3, 4, 5 };

    buffers.VBOBind(3*sizeof(float), vertexes, GL_TRIANGLES);
    buffers.EBOBind(elements, nullptr, GL_UNSIGNED_INT);

    glEnableVertexArrayAttrib(buffers.VertexArrayObject, 0);
    glVertexArrayAttribFormat(buffers.VertexArrayObject, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(buffers.VertexArrayObject, 0, 0);

    Shader shaders("./shaders/vertex.shader", "./shaders/fragment.shader");
    buffers.SetShader(&shaders);

    Renderer renderer(&window, &buffers);

    glClearColor(0.5f, 0.2f, 0.7f, 1.f);
    renderer.Run();

    return 0;
}
