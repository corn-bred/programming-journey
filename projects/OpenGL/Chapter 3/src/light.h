#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>

#include "shaders.h"

class LightHandler {
    public:
    float constant, linear, quadratic;
    LightHandler(float Constant = 1.0f, float Linear = 0.09f, float Quadratic = 0.032f) : constant(Constant), linear(Linear), quadratic(Quadratic) {}
    void addLight(glm::vec3 position, glm::vec3 ambientStrength, glm::vec3 diffuseStrength, glm::vec3 specularStrength, const char *lightclassvar, Shader *shader) {

        for (int i = 0; i < 7; i++) {
            std::stringstream varnames;
            varnames << lightclassvar;
            switch (i) {
                case 0:
                varnames << ".position";
                shader->setVec3(varnames.str(), position);
                break;
                case 1:
                varnames << ".ambientStrength";
                shader->setVec3(varnames.str(), ambientStrength);
                break;
                case 2:
                varnames << ".diffuseStrength";
                shader->setVec3(varnames.str(), diffuseStrength);
                break;
                case 3:
                varnames << ".specularStrength";
                shader->setVec3(varnames.str(), specularStrength);
                break;
                case 4:
                varnames << ".constant";
                shader->setfloat(varnames.str(), constant);
                break;
                case 5:
                varnames << ".linear";
                shader->setfloat(varnames.str(), linear);
                break;
                case 6:
                varnames << ".quadratic";
                shader->setfloat(varnames.str(), quadratic);
                break;
            }
        }
    }

    void addSpotlight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambientStrength, glm::vec3 diffuseStrength, glm::vec3 specularStrength, float innercutoff, float outercutoff, const char *lightclassvar, Shader *shader) {

        for (int i = 0; i < 10; i++) {
            std::stringstream varnames;
            varnames << lightclassvar;
            switch (i) {
                case 0:
                varnames << ".position";
                shader->setVec3(varnames.str(), position);
                break;
                case 1:
                varnames << ".direction";
                shader->setVec3(varnames.str(), direction);
                break;
                case 2:
                varnames << ".ambientStrength";
                shader->setVec3(varnames.str(), ambientStrength);
                break;
                case 3:
                varnames << ".diffuseStrength";
                shader->setVec3(varnames.str(), diffuseStrength);
                break;
                case 4:
                varnames << ".specularStrength";
                shader->setVec3(varnames.str(), specularStrength);
                break;
                case 5:
                varnames << ".constant";
                shader->setfloat(varnames.str(), constant);
                break;
                case 6:
                varnames << ".linear";
                shader->setfloat(varnames.str(), linear);
                break;
                case 7:
                varnames << ".quadratic";
                shader->setfloat(varnames.str(), quadratic);
                break;
                case 8:
                varnames << ".innercutoff";
                shader->setfloat(varnames.str(), glm::cos(glm::radians(innercutoff)));
                break;
                case 9:
                varnames << ".outercutoff";
                shader->setfloat(varnames.str(), glm::cos(glm::radians(outercutoff)));
                break;
            }
        }
    }

    void addSun(glm::vec3 direction, glm::vec3 ambientStrength, glm::vec3 diffuseStrength, glm::vec3 specularStrength, const char *lightclassvar, Shader *shader) {

        for (int i = 0; i < 7; i++) {
            std::stringstream varnames;
            varnames << lightclassvar;
            switch (i) {
                case 0:
                varnames << ".direction";
                shader->setVec3(varnames.str(), direction);
                break;
                case 1:
                varnames << ".ambientStrength";
                shader->setVec3(varnames.str(), ambientStrength);
                break;
                case 2:
                varnames << ".diffuseStrength";
                shader->setVec3(varnames.str(), diffuseStrength);
                break;
                case 3:
                varnames << ".specularStrength";
                shader->setVec3(varnames.str(), specularStrength);
                break;
            }
        }
    }
};