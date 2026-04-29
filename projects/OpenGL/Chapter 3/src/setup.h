#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

bool setup(GLFWwindow *&window, GLFWmonitor *&monitor, const GLFWvidmode *&mode, int WIDTH, int HEIGHT, GLFWframebuffersizefun frambuffersizefunction, GLFWcursorposfun cursorposfunction, GLFWscrollfun scrollfunction) {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW3.\n";
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "Cornbread Program (press esc to exit)", NULL, NULL);

    if (!window) {
        std::cout << "Failed to create GLFW window.\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress )) {// casts glfwGetProcAddress from GLFWglproc to GLADloadproc
        std::cout << "Failed to initialize GLAD.\n";
        glfwTerminate();
        return false;
    }

    monitor = glfwGetPrimaryMonitor();
    mode = const_cast<GLFWvidmode*>(glfwGetVideoMode(monitor));

    glViewport(0,0,WIDTH,HEIGHT);
    glfwSetWindowPos(window, (mode->width - WIDTH)/2, (mode->height - HEIGHT)/2);
    
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(window, frambuffersizefunction);
    glfwSetCursorPosCallback(window, cursorposfunction);
    glfwSetScrollCallback(window, scrollfunction);
    return true;
}