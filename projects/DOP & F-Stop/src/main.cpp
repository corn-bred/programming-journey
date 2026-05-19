#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shaders.h"
//#include "cubebuffer.h"
//#include "renderer.h" //broken
#include "camera.h"
#include "texturebuffer.h"
#include "buffer.h"
#include "setup.h"
#include "data.h"
#include "light.h"
#include "model.h"

using namespace std;

bool firstMouse = true;

int WIDTH = 800, HEIGHT = 600;
float lastX = (float)(WIDTH)/2, lastY = (float)(HEIGHT)/2;

float deltaTime = 0.0f, lastframe = 0.0f;

bool f11pressed = false, fullscreen = false;

float fov = 45.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

#include "events.h"

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main () {
    cout << "Starting...\n";
    GLFWwindow *window;
    GLFWmonitor *monitor;
    const GLFWvidmode *mode;
    if (!setup(window, monitor, mode, WIDTH, HEIGHT, framebuffer_size_callback, mousecallback, scroll_callback)) {
        cerr << "Failed setup\n";
        return EXIT_FAILURE;
    } else {
        cout << "Setup succeeded\n";
    }

    Shader backpackShader("src/shaders/vertCube.glsl", "src/shaders/fragCube.glsl");
    Shader lightingShader("src/shaders/vertLighting.glsl", "src/shaders/fragLighting.glsl");
    
    
    LightHandler lighthandler(1.0f, 0.09f, 0.032f);

    unsigned int fpsCounter = 0;

    stbi_set_flip_vertically_on_load(true);
    Model backpack("res/backpack.obj"); 

    VertexBuffer lightbuffer(vertices, sizeof(vertices), GL_STATIC_DRAW);
    lightbuffer.addAttribute(0, 8, 3, GL_FLOAT, sizeof(float), 0);

    VertexBuffer quadbuffer(quadVertices, sizeof(quadVertices), GL_STATIC_DRAW);
    quadbuffer.addAttribute(0, 4, 2, GL_FLOAT, sizeof(float), 0);
    quadbuffer.addAttribute(1, 4, 2, GL_FLOAT, sizeof(float), 2);

    Shader screenShader("src/shaders/vertFBO.glsl", "src/shaders/fragFBO.glsl");

    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    GLuint texturecolourbuffer;
    glGenTextures(1, &texturecolourbuffer);
    glBindTexture(GL_TEXTURE_2D, texturecolourbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texturecolourbuffer, 0);

    GLuint RBOtexture;
    glGenTextures(1, &RBOtexture);
    glBindTexture(GL_TEXTURE_2D, RBOtexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, RBOtexture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) { //check if framebuffer requirements are fufilled
        cerr << "ERROR: Framebuffer not complete!\n";
        return EXIT_FAILURE;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    while(!glfwWindowShouldClose(window)) {
        GLenum err;

        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //yeahhhh deltatime
        
        float currentframe = glfwGetTime();
        deltaTime = currentframe - lastframe;
        if (floor(currentframe) != floor(lastframe)) {
            stringstream titlestring;
            titlestring << "Cornbread Program (FPS: " << fpsCounter << ")";
            glfwSetWindowTitle(window, titlestring.str().c_str()); 
            fpsCounter = 0;
        }
        lastframe = currentframe;
        

        processinput(window);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

        camera.updateCamera();
        
        glm::mat4 view = camera.calculateView();

        backpackShader.use();
        backpackShader.setVec3("material.specularStrength", 0.5f, 0.5f, 0.5f);
        backpackShader.setVec3("material.diffuseStrength", 0.5f, 0.5f, 0.5f);
        backpackShader.setVec3("material.specularStrength", 0.5f, 0.5f, 0.5f);
        backpackShader.setfloat("material.shininess", 32.0f);

        backpackShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);

        backpackShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);
        backpackShader.setVec3("viewPos", camera.position);
        
        lighthandler.addSpotlight(camera.position, camera.front, glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(1.0f), 5.0f, 5.0f, "spotlight", &backpackShader);

        backpackShader.setMat4("projection", projection);
        backpackShader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        backpackShader.setMat4("model", model);
        backpack.Draw(backpackShader);

        /*lightingShader.use();
        lightbuffer.bind();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);
        for (int i = 0; i < 4; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            lightingShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }*/
        glDisable(GL_DEPTH_TEST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //sets background to white
        glClear(GL_COLOR_BUFFER_BIT);

        screenShader.use();
        screenShader.setint("screenTexture", 0);
        screenShader.setint("depstenTexture", 1);
        screenShader.setfloat("aTime", currentframe);
        quadbuffer.bind();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texturecolourbuffer);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, RBOtexture);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(0);

        fpsCounter++;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteTextures(1, &RBOtexture);
    glfwTerminate();
    return EXIT_SUCCESS;
}