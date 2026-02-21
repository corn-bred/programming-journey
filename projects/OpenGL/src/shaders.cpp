#include "shaders.h"

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath) {
    std::string vertexCode, fragmentCode;
    std::ifstream vertFile, fragFile;

    vertFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertFile.open(vertexFilePath);
        fragFile.open(fragmentFilePath);

        std::stringstream ssVertex, ssFragment;

        ssVertex << vertFile.rdbuf();
        ssFragment << fragFile.rdbuf();

        vertFile.close();
        fragFile.close();

        vertexCode = ssVertex.str();
        fragmentCode = ssFragment.str();
    }
    catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_UNSUCCESSFULLY_READ\n";
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    int success;
    char infolog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(ID,512, NULL,infolog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setbool(const std::string &unifName, bool val) {
    glUniform1i(glGetUniformLocation(ID, unifName.c_str()), (int)(val) );
}

void Shader::setint(const std::string &unifName, int val) {
    glUniform1i(glGetUniformLocation(ID, unifName.c_str()), val);
}

void Shader::setfloat(const std::string &unifName, float val) {
    glUniform1f(glGetUniformLocation(ID, unifName.c_str()), val);
}