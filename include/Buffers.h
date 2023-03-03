#pragma once
#include <main.h>
#include <Shader.h>

class Buffers {
private:
    GLenum DrawMode, ElementType;
    GLsizei ElementCount;
    const GLvoid* ElementsOffset;

    Shader* MainShader = nullptr;
public:

    GLuint VertexArrayObject;
    GLuint VertexBufferObject;
    GLuint ElementBufferObject;

    Buffers();

    //Fixed size buffer
    void VBOBind(GLsizei stride, std::vector<float> data, GLenum mode);
    void EBOBind(std::vector<unsigned int> data, const GLvoid* offset, GLenum type);

    //Variadic size buffer
    void VBOBind(GLsizei stride, std::vector<float> data, GLenum flags, GLenum mode);
    void EBOBind(std::vector<unsigned int> data, GLenum flags, const GLvoid* offset, GLenum type);

    void SetShader(Shader* shader);
    void ClearShader();

    void Draw();

    ~Buffers();
};
