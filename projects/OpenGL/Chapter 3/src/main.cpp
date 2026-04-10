#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "shaders.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

bool firstMouse = true;

int WIDTH = 800, HEIGHT = 600;
float lastX = (float)(WIDTH)/2, lastY = (float)(HEIGHT)/2;
float yaw = -90.0f, pitch = 0.0f;
float deltaTime = 0.0f, lastframe = 0.0f;

bool f11pressed = false, fullscreen = false;

float fov = 45.0f;

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
glm::vec3 cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void framebuffer_size_callback(GLFWwindow *window, int width, int height) { //makes sure GLAD keeps the rendering canvas in sync
    WIDTH = width;
    HEIGHT = height;
    glViewport(0,0,WIDTH,HEIGHT);
}

void processinput(GLFWwindow *window) {
    const float cameraSpeed = 2.5f * deltaTime;
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
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::vec3(cameraFront.x,0,cameraFront.z)) * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::vec3(cameraFront.x,0,cameraFront.z)) * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos += glm::normalize(cameraRight) * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos -= glm::normalize(cameraRight) * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos.y += cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraPos.y -= cameraSpeed;
}

void mousecallback(GLFWwindow *window, double xpos, double ypos) {
    const float sensitivity = 0.1f;

    if (firstMouse || f11pressed) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;
    
    //euler xie
    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 90.0f)
        fov = 90.0f;
}

float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

unsigned int indices[] = {
    0,1,2,
    1,3,2
};

int main () {

    if (!glfwInit()) {
        cout << "Failed to initialize GLFW3.\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Cornbread Program (press esc to exit)", NULL, NULL);

    if (window == NULL) {
        cout << "Failed to create GLFW window.\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress )) {// casts glfwGetProcAddress from GLFWglproc to GLADloadproc
        cout << "Failed to initialize GLAD.\n";
        return -1;
    }

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glViewport(0,0,WIDTH,HEIGHT);
    glfwSetWindowPos(window, (mode->width - WIDTH)/2, (mode->height - HEIGHT)/2);
    
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mousecallback);
    glfwSetScrollCallback(window, scroll_callback);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO); //creates ID for it

    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind the buffer to the job as VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Add the data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (void*)(sizeof(float)*3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float)*8, (void*)(sizeof(float)*6));
    glEnableVertexAttribArray(2);

    GLuint lightingVAO;
    glGenVertexArrays(1, &lightingVAO);
    glBindVertexArray(lightingVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (void*)0);
    glEnableVertexAttribArray(0);
    Shader cubeShader("projects/OpenGL/Chapter 3/src/vertCube.glsl", "projects/OpenGL/Chapter 3/src/fragCube.glsl");
    Shader lightingShader("projects/OpenGL/Chapter 3/src/vertLighting.glsl", "projects/OpenGL/Chapter 3/src/fragLighting.glsl");

    GLuint cratetexture;
    glGenTextures(1, &cratetexture);
    {
        glBindTexture(GL_TEXTURE_2D, cratetexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int width, height, nrchannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("projects/OpenGL/Chapter 3/res/container2.png", &width, &height, &nrchannels, 0);
        if (data) {
            cout << "SUCCESS: " << width << "x" << height << ", channels=" << nrchannels << endl;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {cerr << "Texture failed to load" << endl; return 1;}
        stbi_image_free(data);
    }
    GLuint cratetexturespec;
    glGenTextures(1, &cratetexturespec);
    {
        glBindTexture(GL_TEXTURE_2D, cratetexturespec);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int width, height, nrchannels;
        unsigned char *data = stbi_load("projects/OpenGL/Chapter 3/res/container2_specular.png", &width, &height, &nrchannels, 0);
        if (data) {
            cout << "SUCCESS: " << width << "x" << height << ", channels=" << nrchannels << endl;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {cerr << "Texture failed to load" << endl; return 1;}
        stbi_image_free(data);
    }
    
    while(!glfwWindowShouldClose(window)) {
        //cout << cameraRight.x << ", " << cameraRight.y << ", "<< cameraRight.z << endl;
        //yeahhhh deltatime
        float currentframe = glfwGetTime();
        deltaTime = currentframe - lastframe;
        lastframe = currentframe;  

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

        //Right axis
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        cameraRight = glm::normalize(glm::cross(up, cameraFront));

        //Up axis
        cameraUp = glm::cross(cameraFront, cameraRight);

        const float radius = 10.0f;
        float camX = sin(glfwGetTime())*radius, camZ = cos(glfwGetTime())*radius;
        
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        lightPos = glm::vec3(sin(currentframe) *2.0f, sin(currentframe*5.0f) *0.2f, -cos(currentframe)*2.0f);

        processinput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, cratetexture);

        cubeShader.use();
        cubeShader.setVec3("material.specularStrength", 0.5f, 0.5f, 0.5f);
        cubeShader.setVec3("light.ambientStrength",  0.2f, 0.2f, 0.2f);
        cubeShader.setVec3("light.diffuseStrength",  0.5f, 0.5f, 0.5f);
        cubeShader.setVec3("light.specularStrength", 1.0f, 1.0f, 1.0f); 
        cubeShader.setfloat("material.shininess", 32.0f);
        cubeShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        cubeShader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
        cubeShader.setVec3("lightPos", lightPos);
        cubeShader.setVec3("viewPos", cameraPos);
        cubeShader.setint("material.diffuseStrength", 0);
        cubeShader.setint("material.specularStrength", 1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cratetexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, cratetexturespec);

        glm::mat4 model = glm::mat4(1.0f);
        cubeShader.setMat4("model", model);
        cubeShader.setMat4("projection", projection);
        cubeShader.setMat4("view", view);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        lightingShader.use();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lightingShader.setMat4("model", model);

        glBindVertexArray(lightingVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &lightingVAO);
    
    glfwTerminate();
    return 0;
}