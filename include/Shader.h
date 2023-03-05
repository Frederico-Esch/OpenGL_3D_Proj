#pragma once
#include <main.h>
#include <fstream>
#include <string>
#include <sstream>

class Shader {

    GLuint Program;

    void ReadFileToString(string path, string& out);
    void VerifyCompilation(GLuint shader, string name);
    void VerifyLink(GLuint program, string name);
public:

    Shader(string vertex_shader_path, string fragment_shader_path);
    ~Shader();

    GLint GetUniformLocation(string name);

    void Use(bool clear = false);
    GLuint GetProgram();
};
