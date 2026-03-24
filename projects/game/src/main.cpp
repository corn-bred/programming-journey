#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

float aspect = 16/9; //x:y

int WIDTH = 800, HEIGHT = (float)WIDTH/aspect;

int main () {
    //Initialization
    if (!glfwInit()) {cerr << "GLFW failed to init\n"; return 1;}

    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Game Game", NULL, NULL);
    if (window == NULL) {cerr << "Failed to create window\n"; glfwTerminate(); return 1;}

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)) ) {
        cerr << "GLAD failed to init\n";
        return 1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    //Setup buffers
    //Vertex Array Object (technically not a buffer)
    /*GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData();*/

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}