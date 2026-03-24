#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class RendererHandler {
    public:
    int WIDTH, HEIGHT;

    GLuint ID;
    RendererHandler(int width, int height, char * vertpath, char * fragpath) : WIDTH(width), HEIGHT(height) {
        
    }
};