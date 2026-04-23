#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "buffermanager.h"
#include "shaders.h"

class RenderHandler {
    //static int _NUMBEROFWINDOWS;
    bool _startupInitialize(char *title, GLFWframebuffersizefun sizecallback, GLFWcursorposfun mousecallback, GLFWscrollfun scrollcallback) {
        if (!glfwInit()) {
            std::cout << "Failed to initialize GLFW3.\n";
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window = glfwCreateWindow(WIDTH, HEIGHT, title, NULL, NULL);

        if (window == NULL) {
            std::cout << "Failed to create GLFW window.\n";
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress )) {// casts glfwGetProcAddress from GLFWglproc to GLADloadproc
            std::cout << "Failed to initialize GLAD.\n";
            return false;
        }

        monitor = glfwGetPrimaryMonitor();
        mode = const_cast<GLFWvidmode*>(glfwGetVideoMode(monitor)); //im sorry gang

        glViewport(0,0,WIDTH,HEIGHT);
        glfwSetWindowPos(window, (mode->width - WIDTH)/2, (mode->height - HEIGHT)/2);
    
        glEnable(GL_DEPTH_TEST);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glfwSetFramebufferSizeCallback(window, sizecallback);
        glfwSetCursorPosCallback(window, mousecallback);
        glfwSetScrollCallback(window, scrollcallback);
        return true;
    }

    public:
    int HEIGHT, WIDTH;
    GLFWwindow *window;
    GLFWmonitor* monitor;
    GLFWvidmode* mode;
    std::vector<GLuint> textures;
    BufferManager buffermanager;
    RenderHandler(int width, int height, char *title, GLFWframebuffersizefun sizecallback, GLFWcursorposfun mousecallback, GLFWscrollfun scrollcallback, std::vector<char*> files) : WIDTH(width), HEIGHT(height) {
        //_NUMBEROFWINDOWS++;
        cout << "completed init";
        _startupInitialize(title, sizecallback, mousecallback, scrollcallback);
        
        buffermanager.setupVertexBuffer();
        textures = buffermanager.setupTextures(files);
    }
    ~RenderHandler() {
        //_NUMBEROFWINDOWS--;
    }
};

void updateFrame() {}

void handleUniforms() {}