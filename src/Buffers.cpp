#include <Buffers.h>

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

#ifdef DEBUG_PRINT
    std::cout << "Buffers Deinitialized" << std::endl;
    std::cout << "VAO Deleted" << std::endl;
    std::cout << "VBO Deleted" << std::endl;
    std::cout << "EBO Deleted" << std::endl;
#endif
}

void Buffers::VBOBind(GLsizei stride, std::vector<float> data, GLenum mode) {

    glVertexArrayVertexBuffer(VertexArrayObject, 0, VertexBufferObject, 0, stride);

    glNamedBufferStorage(VertexBufferObject, sizeof(float)*data.size(), data.data(), GL_DYNAMIC_STORAGE_BIT);

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

void Buffers::VBOBind(GLsizei stride, std::vector<float> data, GLenum flags, GLenum mode) {

    glVertexArrayVertexBuffer(VertexArrayObject, 0, VertexBufferObject, 0, stride);

    glNamedBufferData(VertexBufferObject, sizeof(float)*data.size(), data.data(), flags);

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

void Buffers::SetShader(Shader* shader) {
    MainShader = shader;
}

void Buffers::ClearShader() {
    MainShader = nullptr;
}

void Buffers::Draw() {
    glBindVertexArray(VertexArrayObject);
    if(MainShader != nullptr) MainShader->Use();

    glDrawElements(DrawMode, ElementCount, ElementType, ElementsOffset); // Depois do shader usar isso
    //glDrawArrays(GL_TRIANGLES, 0, 3); //Usando isso só para desenhar algo

    if(MainShader != nullptr) MainShader->Use(true);
    glBindVertexArray(0);
}
