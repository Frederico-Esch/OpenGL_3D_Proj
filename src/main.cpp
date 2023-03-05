#include <main.h>
#include <Renderer.h>

int main()
{
    try {

        Window window(800, 600, "Main Window", nullptr, nullptr);
        Buffers buffers;

        std::vector<float> vertexes {
            -.5f,  .5f, 0.f,  ( .5f/3.f), .25f, //x, y, z,    s, t,
             .5f,  .5f, 0.f,  (1.5f/3.f), .25f,
            -.5f, -.5f, 0.f,  ( .5f/3.f), .75f,
             .5f, -.5f, 0.f,  (1.5f/3.f), .75f,

        };

        std::vector<unsigned int> elements { 0, 1, 2, 1, 2, 3 };

        buffers.VBOBind(5*sizeof(float), vertexes, GL_TRIANGLES);
        buffers.EBOBind(elements, nullptr, GL_UNSIGNED_INT);

        glEnableVertexArrayAttrib(buffers.VertexArrayObject, 0);
        glVertexArrayAttribFormat(buffers.VertexArrayObject, 0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(buffers.VertexArrayObject, 0, 0);

        glEnableVertexArrayAttrib(buffers.VertexArrayObject, 1);
        glVertexArrayAttribFormat(buffers.VertexArrayObject, 1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec3));
        glVertexArrayAttribBinding(buffers.VertexArrayObject, 1, 0);

        Shader shaders("./shaders/vertex.shader", "./shaders/fragment.shader");
        buffers.SetShader(&shaders);

        GLint textureLocation = shaders.GetUniformLocation("cubeTexture");

        buffers.LoadTexture("./textures/cube_texture.png",
            { { GL_TEXTURE_WRAP_S, GL_REPEAT }, { GL_TEXTURE_WRAP_T, GL_REPEAT }, { GL_TEXTURE_MIN_FILTER, GL_NEAREST }, { GL_TEXTURE_MAG_FILTER, GL_LINEAR } }
        );
        buffers.SetTextureUnit(textureLocation, 0);

        Renderer renderer(&window, &buffers);

        glClearColor(0.5f, 0.2f, 0.7f, 1.f);
        renderer.Run();
    }
    catch(std::runtime_error e) {
        puts("\n------------");
        puts("ERROR");
        puts("------------\n");
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
