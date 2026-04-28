#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "camera.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) { //makes sure GLAD keeps the rendering canvas in sync
    WIDTH = width;
    HEIGHT = height;
    glViewport(0,0,WIDTH,HEIGHT);
}

void processinput(GLFWwindow *window) {
    const float cameraSpeed = 2.5f;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if(glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS) {
        double xpos, ypos;
        if (!f11pressed) {
        f11pressed = true;
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        if (!fullscreen) {
            glfwMaximizeWindow(window);
            fullscreen = true;
            
        } else {
            fullscreen = false;
            WIDTH = 800;
            HEIGHT = 600;
            glfwRestoreWindow(window);
            glfwSetWindowSize(window, WIDTH, HEIGHT);
            glfwSetWindowPos(window, (mode->width - WIDTH)/2, (mode->height - HEIGHT)/2);
        }
        glViewport(0,0,WIDTH,HEIGHT);
        }
    } else {
        f11pressed = false;
    }
    //euler movement
    /*
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    */
    //game movement
    bool movements[6]; //W:0 S:1 A:2 D:3 SPACE:4 CONTROL:5
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movements[0] = GLFW_PRESS;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movements[1] = GLFW_PRESS;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movements[2] = GLFW_PRESS;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movements[3] = GLFW_PRESS;
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        movements[4] = GLFW_PRESS;
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        movements[5] = GLFW_PRESS;
    
    camera.keyboardprocess(movements, deltaTime, cameraSpeed);
}

void mousecallback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse || f11pressed) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.mouseprocess(xoffset, yoffset, GL_TRUE);
    
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 90.0f)
        fov = 90.0f;
}