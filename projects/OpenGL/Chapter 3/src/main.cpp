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
#include "vertexbuffer.h"
#include "setup.h"
#include "data.h"
#include "light.h"

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
    
    GLFWwindow *window;
    GLFWmonitor *monitor;
    const GLFWvidmode *mode;
    if (!setup(window, monitor, mode, WIDTH, HEIGHT, framebuffer_size_callback, mousecallback, scroll_callback)) {
        cerr << "Failed setup\n";
        return -1;
    }

    VertexBuffer cubebuffer(vertices, sizeof(vertices), GL_STATIC_DRAW);
    cubebuffer.addAttribute(0, 8, 3, GL_FLOAT, sizeof(float), 0);
    cubebuffer.addAttribute(1, 8, 3, GL_FLOAT, sizeof(float), 3);
    cubebuffer.addAttribute(2, 8, 2, GL_FLOAT, sizeof(float), 6);

    VertexBuffer lightbuffer(vertices, sizeof(vertices), GL_STATIC_DRAW);
    cubebuffer.addAttribute(0, 8, 3, GL_FLOAT, sizeof(float), 0);
    
    //RenderHandler renderer(600, 800, "Cornbread Program (Press esc to exit)", framebuffer_size_callback, mousecallback, scroll_callback, files);
    TextureBuffer cratetexture("projects/OpenGL/Chapter 3/res/container2.png");
    TextureBuffer cratetexturespec("projects/OpenGL/Chapter 3/res/container2_specular.png");
    TextureBuffer cratetexturebump("projects/OpenGL/Chapter 3/res/container2_normal.png");
    TextureBuffer cratetextureambient("projects/OpenGL/Chapter 3/res/container2_ambient.png");
    

    Shader cubeShader("projects/OpenGL/Chapter 3/src/shaders/vertCube.glsl", "projects/OpenGL/Chapter 3/src/shaders/fragCube.glsl");
    Shader lightingShader("projects/OpenGL/Chapter 3/src/shaders/vertLighting.glsl", "projects/OpenGL/Chapter 3/src/shaders/fragLighting.glsl");
    
    LightHandler lighthandler(1.0f, 0.09f, 0.032f);

    unsigned int fpsCounter = 0;

    while(!glfwWindowShouldClose(window)) {//breaks here
        //yeahhhh deltatime
        
        float currentframe = glfwGetTime();
        deltaTime = currentframe - lastframe;
        if (floor(currentframe) != floor(lastframe)) {
            stringstream titlestring;
            titlestring << "Cornbread Program (FPS: " << fpsCounter << ")";
            //glfwSetWindowTitle(window, titlestring.str().c_str()); 
            //fpsCounter = 0;
        }
        lastframe = currentframe;  
        

        //lightPos = glm::vec3(sin(currentframe) *2.0f, sin(currentframe*5.0f) *0.2f, -cos(currentframe)*2.0f);

        processinput(window);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

        camera.updateCamera();
        
        glm::mat4 view = camera.calculateView();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glBindTexture(GL_TEXTURE_2D, renderer.textures[0]);

        cubeShader.use();
        cubeShader.setVec3("material.specularStrength", 0.5f, 0.5f, 0.5f);

        float lightstrength = 3.0f;
        cubeShader.setVec3("light.ambientStrength",  0.2f, 0.2f, 0.2f);
        cubeShader.setVec3("light.diffuseStrength",  0.5f*lightstrength, 0.5f*lightstrength, 0.5f*lightstrength);
        cubeShader.setVec3("light.specularStrength", 1.0f*lightstrength, 1.0f*lightstrength, 1.0f*lightstrength); 

        cubeShader.setfloat("material.shininess", 32.0f);
        cubeShader.setfloat("material.bumpstrength", 10.5f);

        cubeShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);

        //cubeShader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
        cubeShader.setVec3("lightPos", camera.position);

        cubeShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);
        cubeShader.setVec3("viewPos", camera.position);

        cubeShader.setint("material.diffuseStrength", 0);
        cubeShader.setint("material.specularStrength", 1);
        cubeShader.setint("material.ambientStrength", 2);

        cubeShader.setint("material.normalmap", 3);

        cubeShader.setVec3("sun.direction", -0.2f, -1.0f, -0.3f);
        cubeShader.setVec3("sun.ambientStrength", 0.05f, 0.05f, 0.05f);
        cubeShader.setVec3("sun.diffuseStrength", 0.4f, 0.4f, 0.4f);
        cubeShader.setVec3("sun.specularStrength", 0.5f, 0.5f, 0.5f);

        // point light 1
        lighthandler.addLight(pointLightPositions[0], glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), "pointLights[0]", &cubeShader);
        // point light 2
        lighthandler.addLight(pointLightPositions[1], glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), "pointLights[1]", &cubeShader);
        // point light 3
        lighthandler.addLight(pointLightPositions[2], glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), "pointLights[2]", &cubeShader);
        // point light 4
        lighthandler.addLight(pointLightPositions[3], glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), "pointLights[3]", &cubeShader);
        // spotLight
        cubeShader.setVec3("spotlight.position", camera.position);
        cubeShader.setVec3("spotlight.direction", camera.front);
        cubeShader.setVec3("spotlight.ambientStrength", 0.0f, 0.0f, 0.0f);
        cubeShader.setVec3("spotlight.diffuseStrength", 1.0f, 1.0f, 1.0f);
        cubeShader.setVec3("spotlight.specularStrength", 1.0f, 1.0f, 1.0f);
        cubeShader.setfloat("spotlight.constant", 1.0f);
        cubeShader.setfloat("spotlight.linear", 0.09f);
        cubeShader.setfloat("spotlight.quadratic", 0.032f);
        cubeShader.setfloat("spotlight.innercutoff", glm::cos(glm::radians(12.5f)));
        cubeShader.setfloat("spotlight.outercutoff", glm::cos(glm::radians(15.0f)));    

        glm::mat4 model = glm::mat4(1.0f);
        cubeShader.setMat4("model", model);
        cubeShader.setMat4("projection", projection);
        cubeShader.setMat4("view", view);

        /*glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cratetexture); //texture colour
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, cratetexturespec); //speculation
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, cratetextureambient); //ambience
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, cratetexturebump); //bump*/
        cratetexture.bindTexture();
        cratetexturespec.bindTexture();
        cratetextureambient.bindTexture();
        cratetexturebump.bindTexture();
        
        cubebuffer.bind();
        for (int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = i * 20.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            cubeShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        /*lightingShader.use();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lightingShader.setMat4("model", model);

        glBindVertexArray(lightingVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);*/
        glBindVertexArray(0);

        fpsCounter++;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}