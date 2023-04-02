#pragma once
#include <main.h>
#include <Shader.h>

struct Attribute {
    GLint count;
    GLenum type;
    GLboolean normalized;
    GLuint relative_offset;
};

class Buffers {
private:
    GLenum DrawMode, ElementType;
    GLsizei ElementCount;
    const GLvoid* ElementsOffset;
    std::vector<Attribute> attribs;

    Shader* MainShader = nullptr;

    GLuint Texture = 0;
    GLint TextureUnit = -1;
public:

    GLuint VertexArrayObject;
    GLuint VertexBufferObject;
    GLuint ElementBufferObject;

    Buffers();

    //Fixed size buffer
    void VBOBind(GLsizei stride, std::vector<Vertex> data, GLenum mode);
    void EBOBind(std::vector<unsigned int> data, const GLvoid* offset, GLenum type);

    //Variadic size buffer
    void VBOBind(GLsizei stride, std::vector<Vertex> data, GLenum flags, GLenum mode);
    void EBOBind(std::vector<unsigned int> data, GLenum flags, const GLvoid* offset, GLenum type);

    void PushAttribute(Attribute attrib);

    void LoadTexture(string texture_path, std::vector<std::pair<GLenum, GLint>> parameters);
    void DeleteTexture();

    void SetTextureUnit(GLint textureLocation, GLuint unit);

    void SetShader(Shader* shader);
    void ClearShader();

    void Draw();

    ~Buffers();
};
