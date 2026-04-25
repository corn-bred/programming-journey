#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "shaders.h"
#include "vertexbuffer.h"
//#include "renderer.h" //broken
#include "camera.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

bool firstMouse = true;

int WIDTH = 800, HEIGHT = 600;
float lastX = (float)(WIDTH)/2, lastY = (float)(HEIGHT)/2;

float deltaTime = 0.0f, lastframe = 0.0f;

bool f11pressed = false, fullscreen = false;

float fov = 45.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

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
    Movement movement = NONE;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movement = FORWARD;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movement = BACKWARD;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movement = LEFT;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movement = RIGHT;
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        movement = UP;
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        movement = DOWN;
    
    camera.keyboardprocess(movement, deltaTime, cameraSpeed);
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

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] = {
    glm::vec3( 0.7f,  0.2f,  2.0f),
    glm::vec3( 2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3( 0.0f,  0.0f, -3.0f)
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

    /*GLuint VAO;
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
    glEnableVertexAttribArray(2);*/
    VertexBuffer vertexbuffer(vertices, sizeof(vertices), GL_STATIC_DRAW);
    vertexbuffer.addAttribute(0, 8, 3, GL_FLOAT, sizeof(float), 0);
    vertexbuffer.addAttribute(1, 8, 3, GL_FLOAT, sizeof(float), 3);
    vertexbuffer.addAttribute(2, 8, 2, GL_FLOAT, sizeof(float), 6);
    /*GLuint lightingVAO;
    glGenVertexArrays(1, &lightingVAO);
    glBindVertexArray(lightingVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (void*)0);
    glEnableVertexAttribArray(0);*/
    

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
    GLuint cratetexturebump;
    glGenTextures(1, &cratetexturebump);
    {
        glBindTexture(GL_TEXTURE_2D, cratetexturebump);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int width, height, nrchannels;
        unsigned char *data = stbi_load("projects/OpenGL/Chapter 3/res/container2_normal.png", &width, &height, &nrchannels, 0);
        if (data) {
            cout << "SUCCESS: " << width << "x" << height << ", channels=" << nrchannels << endl;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {cerr << "Texture failed to load" << endl; return 1;}
        stbi_image_free(data);
    }
    GLuint cratetextureambient;
    glGenTextures(1, &cratetextureambient);
    {
        glBindTexture(GL_TEXTURE_2D, cratetextureambient);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int width, height, nrchannels;
        unsigned char *data = stbi_load("projects/OpenGL/Chapter 3/res/container2_ambient.png", &width, &height, &nrchannels, 0);
        if (data) {
            cout << "SUCCESS: " << width << "x" << height << ", channels=" << nrchannels << endl;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {cerr << "Texture failed to load" << endl; return 1;}
        stbi_image_free(data);
    }
    /*vector<char*> files = {
        "projects/OpenGL/Chapter 3/res/container2.png",
        "projects/OpenGL/Chapter 3/res/container2_specular.png",
        "projects/OpenGL/Chapter 3/res/container2_normal.png"
    };*/
    //RenderHandler renderer(600, 800, "Cornbread Program (Press esc to exit)", framebuffer_size_callback, mousecallback, scroll_callback, files);

    Shader cubeShader("projects/OpenGL/Chapter 3/src/shaders/vertCube.glsl", "projects/OpenGL/Chapter 3/src/shaders/fragCube.glsl");
    Shader lightingShader("projects/OpenGL/Chapter 3/src/shaders/vertLighting.glsl", "projects/OpenGL/Chapter 3/src/shaders/fragLighting.glsl");
    
    while(!glfwWindowShouldClose(window)) {
        //cout << cameraRight.x << ", " << cameraRight.y << ", "<< cameraRight.z << endl;
        //yeahhhh deltatime
        float currentframe = glfwGetTime();
        deltaTime = currentframe - lastframe;
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
        cubeShader.setVec3("pointLights[0].position", pointLightPositions[0]);
        cubeShader.setVec3("pointLights[0].ambientStrength", 0.05f, 0.05f, 0.05f);
        cubeShader.setVec3("pointLights[0].diffuseStrength", 0.8f, 0.8f, 0.8f);
        cubeShader.setVec3("pointLights[0].specularStrength", 1.0f, 1.0f, 1.0f);
        cubeShader.setfloat("pointLights[0].constant", 1.0f);
        cubeShader.setfloat("pointLights[0].linear", 0.09f);
        cubeShader.setfloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        cubeShader.setVec3("pointLights[1].position", pointLightPositions[1]);
        cubeShader.setVec3("pointLights[1].ambientStrength", 0.05f, 0.05f, 0.05f);
        cubeShader.setVec3("pointLights[1].diffuseStrength", 0.8f, 0.8f, 0.8f);
        cubeShader.setVec3("pointLights[1].specularStrength", 1.0f, 1.0f, 1.0f);
        cubeShader.setfloat("pointLights[1].constant", 1.0f);
        cubeShader.setfloat("pointLights[1].linear", 0.09f);
        cubeShader.setfloat("pointLights[1].quadratic", 0.032f);
        // point light 3
        cubeShader.setVec3("pointLights[2].position", pointLightPositions[2]);
        cubeShader.setVec3("pointLights[2].ambientStrength", 0.05f, 0.05f, 0.05f);
        cubeShader.setVec3("pointLights[2].diffuseStrength", 0.8f, 0.8f, 0.8f);
        cubeShader.setVec3("pointLights[2].specularStrength", 1.0f, 1.0f, 1.0f);
        cubeShader.setfloat("pointLights[2].constant", 1.0f);
        cubeShader.setfloat("pointLights[2].linear", 0.09f);
        cubeShader.setfloat("pointLights[2].quadratic", 0.032f);
        // point light 4
        cubeShader.setVec3("pointLights[3].position", pointLightPositions[3]);
        cubeShader.setVec3("pointLights[3].ambientStrength", 0.05f, 0.05f, 0.05f);
        cubeShader.setVec3("pointLights[3].diffuseStrength", 0.8f, 0.8f, 0.8f);
        cubeShader.setVec3("pointLights[3].specularStrength", 1.0f, 1.0f, 1.0f);
        cubeShader.setfloat("pointLights[3].constant", 1.0f);
        cubeShader.setfloat("pointLights[3].linear", 0.09f);
        cubeShader.setfloat("pointLights[3].quadratic", 0.032f);
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

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cratetexture); //texture colour
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, cratetexturespec); //speculation
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, cratetextureambient); //ambience
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, cratetexturebump); //bump
        
        glBindVertexArray(vertexbuffer.VAO);
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

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}