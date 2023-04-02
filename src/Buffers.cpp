#include <Buffers.h>
#pragma warning(push)
#pragma warning(disable: 4244)
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#pragma warning(pop)

Buffers::Buffers() {
    glCreateVertexArrays(1, &VertexArrayObject);
    glCreateBuffers(1, &VertexBufferObject);
    glCreateBuffers(1, &ElementBufferObject);

    std::cout << VertexArrayObject << std::endl;
#ifdef DEBUG_PRINT
    std::cout << "Buffers Initialized" << std::endl;
    std::cout << "VAO VBO EBO Initialized" << std::endl;
#endif
}

Buffers::~Buffers() {
    glDeleteVertexArrays(1, &VertexArrayObject);
    glDeleteBuffers(1, &VertexBufferObject);
    glDeleteBuffers(1, &ElementBufferObject);
    glDeleteTextures(1, &Texture);

#ifdef DEBUG_PRINT
    std::cout << "Buffers Deinitialized" << std::endl;
    std::cout << "VAO Deleted" << std::endl;
    std::cout << "VBO Deleted" << std::endl;
    std::cout << "EBO Deleted" << std::endl;
#endif
}

void Buffers::VBOBind(GLsizei stride, std::vector<Vertex> data, GLenum mode) {

    glVertexArrayVertexBuffer(VertexArrayObject, 0, VertexBufferObject, 0, stride);

    glNamedBufferStorage(VertexBufferObject, sizeof(data[0])*data.size(), data.data(), GL_DYNAMIC_STORAGE_BIT);

    DrawMode = mode;

#ifdef DEBUG_PRINT
    std::cout << "VBO binded with fixed size" << std::endl;
#endif
}

void Buffers::EBOBind(std::vector<unsigned int> data, const GLvoid* offset, GLenum type) {

    glVertexArrayElementBuffer(VertexArrayObject, ElementBufferObject);

    glNamedBufferStorage(ElementBufferObject, sizeof(int)*data.size(), data.data(), GL_DYNAMIC_STORAGE_BIT);

    ElementsOffset = (const GLvoid*)offset;
    ElementCount = (GLsizei)data.size();
    ElementType = type;


#ifdef DEBUG_PRINT
    std::cout << "EBO binded with fixed size" << std::endl;
#endif
}

void Buffers::VBOBind(GLsizei stride, std::vector<Vertex> data, GLenum flags, GLenum mode) {

    glVertexArrayVertexBuffer(VertexArrayObject, 0, VertexBufferObject, 0, stride);

    glNamedBufferData(VertexBufferObject, sizeof(data[0])*data.size(), data.data(), flags);

    DrawMode = mode;

#ifdef DEBUG_PRINT
    std::cout << "VBO binded with variadic size" << std::endl;
#endif
}

void Buffers::EBOBind(std::vector<unsigned int> data, GLenum flags, const GLvoid* offset, GLenum type) {

    glVertexArrayElementBuffer(VertexArrayObject, ElementBufferObject);

    glNamedBufferData(ElementBufferObject, sizeof(int)*data.size(), data.data(), flags);

    ElementsOffset = (const GLvoid*)offset;
    ElementCount = (GLsizei)data.size();
    ElementType = type;

#ifdef DEBUG_PRINT
    std::cout << "EBO binded with variadic size" << std::endl;
#endif
}

void Buffers::PushAttribute(Attribute attribute) {
    GLuint attribute_index = (GLuint)attribs.size();
    attribs.push_back(attribute);

    glEnableVertexArrayAttrib (VertexArrayObject, attribute_index);
    glVertexArrayAttribFormat (VertexArrayObject, attribute_index, attribute.count, attribute.type, attribute.normalized, attribute.relative_offset);
    glVertexArrayAttribBinding(VertexArrayObject, attribute_index, 0);
}

void Buffers::LoadTexture(string texture_path, std::vector<std::pair<GLenum, GLint>> parameters) {

    if (Texture != 0) {
#ifdef DEBUG_PRINT
        std::cout << "Texture already loaded clean it up first" << std::endl;
#endif
        return;
    }

    int width, height;
    int n_channels;
    stbi_uc* data = stbi_load(texture_path.c_str(), &width, &height, &n_channels, STBI_rgb_alpha);
#ifdef DEBUG_PRINT
    std::cout << "\nwidth: " << width << "\nheight: " << height << "\nn_channels: " << n_channels << std::endl;
#endif
    if (n_channels != 4) throw std::runtime_error("Wrong number of channels");

    glCreateTextures(GL_TEXTURE_2D, 1, &Texture);
    glTextureStorage2D(Texture, 1, GL_RGBA8, width, height);
    glTextureSubImage2D(Texture, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

    for (auto [ param, value ] : parameters) { glTextureParameteri(Texture, param, value); }

    stbi_image_free(data);
}

void Buffers::DeleteTexture() {
    glDeleteTextures(1, &Texture);
    Texture = 0;
}

void Buffers::SetTextureUnit(GLint textureLocation, GLuint unit) {
    if ( MainShader == nullptr) throw std::runtime_error("No shader to use");
    if (textureLocation < 0) throw std::runtime_error("Texture location is incorrect");
    MainShader->Use();

    glUniform1i(textureLocation, unit);
    TextureUnit = unit;

    MainShader->Use(true);
}

void Buffers::SetShader(Shader* shader) {
    MainShader = shader;
}

void Buffers::ClearShader() {
    MainShader = nullptr;
}

void Buffers::Draw() {
    glBindVertexArray(VertexArrayObject);
    if(MainShader != nullptr) MainShader->Use();

    if ( Texture > 0 && TextureUnit > -1) glBindTextureUnit(TextureUnit, Texture);

    glDrawElements(DrawMode, ElementCount, ElementType, ElementsOffset); // Depois do shader usar isso
    //glDrawArrays(GL_TRIANGLES, 0, 3); //Usando isso só para desenhar algo

    glBindTextureUnit(0, 0);

    if(MainShader != nullptr) MainShader->Use(true);
    glBindVertexArray(0);
}
