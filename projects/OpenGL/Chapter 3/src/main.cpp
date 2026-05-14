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
        return -1;
    } else {
        cout << "Setup succeeded\n";
    }

    VertexBuffer lightbuffer(vertices, sizeof(vertices), GL_STATIC_DRAW);
    lightbuffer.addAttribute(0, 8, 3, GL_FLOAT, sizeof(float), 0);
    

    //Shader backpackShader("projects/OpenGL/Chapter 3/src/shaders/vertCube.glsl", "projects/OpenGL/Chapter 3/src/shaders/fragCube.glsl");
    //Shader lightingShader("projects/OpenGL/Chapter 3/src/shaders/vertLighting.glsl", "projects/OpenGL/Chapter 3/src/shaders/fragLighting.glsl");
    //Shader stencilShader("projects/OpenGL/Chapter 3/src/shaders/vertStencil.glsl", "projects/OpenGL/Chapter 3/src/shaders/fragStencil.glsl");

    Shader blendingShader("projects/OpenGL/Chapter 3/src/shaders/vertBlending.glsl", "projects/OpenGL/Chapter 3/src/shaders/fragBlending.glsl");
    VertexBuffer grassbuffer(transparentVertices, sizeof(transparentVertices), GL_STATIC_DRAW);
    grassbuffer.addAttribute(0, 5, 3, GL_FLOAT, sizeof(float), 0);
    grassbuffer.addAttribute(1, 5, 2, GL_FLOAT, sizeof(float), 3);
    TextureBuffer grassTexture("projects/OpenGL/Chapter 3/res/blending_transparent_window.png", GL_RGBA);
    
    LightHandler lighthandler(1.0f, 0.09f, 0.032f);

    unsigned int fpsCounter = 0;

    

    Model backpack("projects/OpenGL/Chapter 3/res/backpack.obj"); 

    std::cout << "VAO ID: " << grassbuffer.VAO << std::endl;
    std::cout << "VBO ID: " << grassbuffer.VBO << std::endl;
    std::cout << "Shader ID: " << blendingShader.ID << std::endl;




    while(!glfwWindowShouldClose(window)) {
        GLenum err;
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

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
        
        //glStencilFunc(GL_ALWAYS, 1, 0xFF);
        //glStencilMask(0xFF);

        /*backpackShader.use();
        backpackShader.setVec3("material.specularStrength", 0.5f, 0.5f, 0.5f);
        backpackShader.setVec3("material.diffuseStrength", 0.5f, 0.5f, 0.5f);
        backpackShader.setVec3("material.specularStrength", 0.5f, 0.5f, 0.5f);
        backpackShader.setfloat("material.shininess", 32.0f);
        //backpackShader.setfloat("material.bumpstrength", 10.5f);

        backpackShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);

        backpackShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);
        backpackShader.setVec3("viewPos", camera.position);
        backpackShader.setMat4("projection", projection);
        backpackShader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        backpackShader.setMat4("model", model);*/
        //backpack.Draw(backpackShader);

        //lighthandler.addSun(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.05f), glm::vec3(0.4f), glm::vec3(0.5f), "sun", &backpackShader);

        // point light 1
        //lighthandler.addLight(pointLightPositions[0], glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), "pointLights[0]", &backpackShader);
        // point light 2
        //lighthandler.addLight(pointLightPositions[1], glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), "pointLights[1]", &backpackShader);
        // point light 3
        //lighthandler.addLight(pointLightPositions[2], glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), "pointLights[2]", &backpackShader);
        // point light 4
        //lighthandler.addLight(pointLightPositions[3], glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), "pointLights[3]", &backpackShader);
        // spotLight
        lighthandler.addSpotlight(camera.position, camera.front, glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(1.0f), 5.0f, 5.0f, "spotlight", &blendingShader);

        

        /*glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);
        stencilShader.use();
        stencilShader.setMat4("projection", projection);
        stencilShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f));
        model = glm::scale(model, glm::vec3(1.1f));
        stencilShader.setMat4("model", model);
        backpack.Draw(stencilShader);
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glEnable(GL_DEPTH_TEST); */

        std::map<float, glm::vec3> sorted;
        for (unsigned int i = 0; i < vegetation.size(); i++) {
            float distance = glm::length(camera.position - vegetation[i]);
            sorted[distance] = vegetation[i];
        }
        
        blendingShader.use();
        grassbuffer.bind();
        blendingShader.setMat4("projection", projection);
        blendingShader.setMat4("view", view);
        blendingShader.setint("Texture", 0);
        
        grassTexture.bindTexture(0);
        for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, it->second);
            blendingShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

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

        glBindVertexArray(0);

        fpsCounter++;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}