#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
    public:
    GLuint ID;
    
    Shader(const char* vertexFilePath, const char* fragmentFilePath);

    void use();

    void setbool(const std::string &unifName, bool val);
    void setint(const std::string &unifName, int val);
    void setfloat(const std::string &unifName, float val);
};

#endif