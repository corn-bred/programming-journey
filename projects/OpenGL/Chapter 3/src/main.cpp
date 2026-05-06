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

    /*VertexBuffer cubebuffer(vertices, sizeof(vertices), GL_STATIC_DRAW);
    cubebuffer.addAttribute(0, 8, 3, GL_FLOAT, sizeof(float), 0);
    cubebuffer.addAttribute(1, 8, 3, GL_FLOAT, sizeof(float), 3);
    cubebuffer.addAttribute(2, 8, 2, GL_FLOAT, sizeof(float), 6);*/

    VertexBuffer lightbuffer(vertices, sizeof(vertices), GL_STATIC_DRAW);
    lightbuffer.addAttribute(0, 8, 3, GL_FLOAT, sizeof(float), 0);
    
    //RenderHandler renderer(600, 800, "Cornbread Program (Press esc to exit)", framebuffer_size_callback, mousecallback, scroll_callback, files);
    //TextureBuffer cratetexture("projects/OpenGL/Chapter 3/res/container2.png");
    //TextureBuffer cratetexturespec("projects/OpenGL/Chapter 3/res/container2_specular.png");
    //TextureBuffer cratetexturebump("projects/OpenGL/Chapter 3/res/container2_normal.png");
    //TextureBuffer cratetextureambient("projects/OpenGL/Chapter 3/res/container2_ambient.png");
    

    Shader backpackShader("projects/OpenGL/Chapter 3/src/shaders/vertCube.glsl", "projects/OpenGL/Chapter 3/src/shaders/fragCube.glsl");
    Shader lightingShader("projects/OpenGL/Chapter 3/src/shaders/vertLighting.glsl", "projects/OpenGL/Chapter 3/src/shaders/fragLighting.glsl");
    
    LightHandler lighthandler(1.0f, 0.09f, 0.032f);

    unsigned int fpsCounter = 0;

    stbi_set_flip_vertically_on_load(true);

    Model backpack("projects/OpenGL/Chapter 3/res/backpack.obj"); 

    while(!glfwWindowShouldClose(window)) {
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

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        backpackShader.use();
        backpackShader.setVec3("material.specularStrength", 0.5f, 0.5f, 0.5f);
        backpackShader.setVec3("material.diffuseStrength", 0.5f, 0.5f, 0.5f);
        backpackShader.setVec3("material.specularStrength", 0.5f, 0.5f, 0.5f);
        backpackShader.setfloat("material.shininess", 32.0f);
        //backpackShader.setfloat("material.bumpstrength", 10.5f);

        backpackShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);

        backpackShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);
        backpackShader.setVec3("viewPos", camera.position);

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
        lighthandler.addSpotlight(camera.position, camera.front, glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(1.0f), 5.0f, 5.0f, "spotlight", &backpackShader);

        backpackShader.setMat4("projection", projection);
        backpackShader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
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

        glBindVertexArray(0);

        fpsCounter++;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}