#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class TextureBuffer {
    GLuint texture;
    static inline unsigned int numberOfTextures = 0;
    const unsigned int textureID;
    public:
    TextureBuffer(const char *texturepath, GLenum wrappingS = GL_MIRRORED_REPEAT, GLenum wrappingT = GL_MIRRORED_REPEAT, GLenum min = GL_NEAREST_MIPMAP_LINEAR, GLenum mag = GL_LINEAR) : textureID(numberOfTextures) {
        ++numberOfTextures;
        std::cerr << "TextureID = " << textureID << std::endl;
        glGenTextures(1, &texture);
        {
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingS);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
            int width, height, nrchannels;
            stbi_set_flip_vertically_on_load(true);
            unsigned char *data = stbi_load("projects/OpenGL/Chapter 3/res/container2.png", &width, &height, &nrchannels, 0);
            if (data) {
                std::cerr << "SUCCESS: " << width << "x" << height << ", channels=" << nrchannels << std::endl;
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {std::cerr << "Texture ID" << textureID << "failed to load" << std::endl; return;}
            stbi_image_free(data);
        }
    }

    ~TextureBuffer() {
        numberOfTextures--;
        glDeleteTextures(1, &texture);
    }

    void bindTexture() {
        glActiveTexture(GL_TEXTURE0 + textureID);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
};