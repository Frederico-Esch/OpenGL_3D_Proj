#include <Shader.h>

void Shader::ReadFileToString(string path, string& out) {
    std::stringstream content;
    std::fstream file(path, std::ios::in);

    string line = "";
    while (!file.eof()) {
        std::getline(file, line);
        content << line << '\n';
    }

    file.close();
    out = content.str();
}

void Shader::VerifyCompilation(GLuint shader, string name) {

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

#ifdef DEBUG_PRINT
    std::cout << "Compilation Status of " << name << " Shader: " << success << std::endl;
    if (!success) {
        std::array<char, 1024> info;
        info.fill('\0');
        glGetShaderInfoLog(shader, (GLsizei)info.size(), NULL, info.data());
        std::cout << info.data() << std::endl;
    }
#endif

    if (!success) throw std::runtime_error("Compilation Error in the " + name + " Shader");
}

GLint Shader::GetUniformLocation(string name) {
    GLint uniform = glGetUniformLocation(Program, name.c_str());
    if ( uniform < 0 ) throw std::runtime_error("Uniform does not exist");
    return (GLuint) uniform;
}

void Shader::VerifyLink(GLuint program, string name) {
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

#ifdef DEBUG_PRINT
    std::cout << "Compilation Status of " << name << " Program: " << success << std::endl;
    if (!success) {
        std::array<char, 1024> info;
        info.fill('\0');
        glGetProgramInfoLog(program, (GLsizei)info.size(), NULL, info.data());
        std::cout << info.data() << std::endl;
    }
#endif

    if (!success) throw std::runtime_error("Linking Error in the " + name + " Program");
}

Shader::Shader(string vertex_shader_path, string fragment_shader_path) {
    Program  = glCreateProgram();
    GLuint vertex   = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    string content;
    ReadFileToString(vertex_shader_path, content);
    const char* vertex_shader_content = content.c_str();
    glShaderSource(vertex, 1, &vertex_shader_content, NULL);
    glCompileShader(vertex);

    VerifyCompilation(vertex, "Vertex Shader");

    content = "";
    ReadFileToString(fragment_shader_path, content);
    const char* fragment_shader_content = content.c_str();
    glShaderSource(fragment, 1, &fragment_shader_content, NULL);
    glCompileShader(fragment);

    VerifyCompilation(fragment, "Fragment");

    glAttachShader(Program, vertex);
    glAttachShader(Program, fragment);
    glLinkProgram(Program);

    VerifyLink(Program, "Main Program");

    glDetachShader(Program, vertex);
    glDetachShader(Program, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    vertex = 0;
    fragment = 0;

#ifdef DEBUG_PRINT
    std::cout << "Shader Initialized" << std::endl;
    std::cout << "Program Created and Linked" << std::endl;
#endif
}

Shader::~Shader() {
    glDeleteProgram(Program);

#ifdef DEBUG_PRINT
    std::cout << "Shader Deinitialized" << std::endl;
    std::cout << "Program Deleted" << std::endl;
#endif
}

GLuint Shader::GetProgram() { return Program; }

void Shader::Use(bool clear) {
    if (clear) glUseProgram(0);
    else glUseProgram(Program);
}
