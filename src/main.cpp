#include <main.h>
#include <Renderer.h>

int main()
{
    try {

        Window window(800, 600, "Main Window", nullptr, nullptr);
        Buffers buffers;

        std::vector<Vertex> vertexes {
            Vertex(glm::vec3(-.75f, .25f, 0.f),  glm::vec2((1.5f/3.f), .25f)), //x, y, z,    s, t,
            Vertex(glm::vec3(-.25f, .25f, 0.f),  glm::vec2((2.5f/3.f), .25f)),
            Vertex(glm::vec3(-.75f, .75f, 0.f),  glm::vec2((1.5f/3.f), .75f)),
            Vertex(glm::vec3(-.25f, .75f, 0.f),  glm::vec2((2.5f/3.f), .75f)),

            Vertex(glm::vec3(.75f, -.25f, 0.f),  glm::vec2((.0f/3.f), .0f)), //x, y, z,    s, t,
            Vertex(glm::vec3(.25f, -.25f, 0.f),  glm::vec2((1.f/3.f), .5f)),
            Vertex(glm::vec3(.75f, -.75f, 0.f),  glm::vec2((.0f/3.f), .0f)),
            Vertex(glm::vec3(.25f, -.75f, 0.f),  glm::vec2((1.f/3.f), .5f)),
        };

        std::vector<unsigned int> elements {
            0, 1, 2, 1, 2, 3, /* first  square */
            4, 5, 6, 5, 6, 7, /* second square */
        };

        buffers.VBOBind(sizeof(Vertex), vertexes, GL_TRIANGLES);
        buffers.EBOBind(elements, nullptr, GL_UNSIGNED_INT);

        buffers.PushAttribute({ 3, GL_FLOAT, GL_FALSE, 0 });
        buffers.PushAttribute({ 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) });

        Shader shaders("./shaders/vertex.shader", "./shaders/fragment.shader");
        buffers.SetShader(&shaders);

        GLint textureLocation = shaders.GetUniformLocation("cubeTexture");

        buffers.LoadTexture("./textures/cube_texture.png",
            { { GL_TEXTURE_WRAP_S, GL_REPEAT }, { GL_TEXTURE_WRAP_T, GL_REPEAT }, { GL_TEXTURE_MIN_FILTER, GL_NEAREST }, { GL_TEXTURE_MAG_FILTER, GL_LINEAR } }
        );
        buffers.SetTextureUnit(textureLocation, 0);

        Renderer renderer(&window, &buffers);

        glClearColor(0.5f, 0.2f, 0.7f, 1.f);
        renderer.SetupBlending();
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
