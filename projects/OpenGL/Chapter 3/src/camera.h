#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NONE
};

class Camera {
    public:
    glm::vec3 position;
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
    float yaw = -90.0f, pitch = 0.0f;

    

    Camera(glm::vec3 cameraPos) : position(cameraPos) {}
    Camera() : position(glm::vec3(0.0f)) {}

    void updateCamera() {
        //Right axis
        glm::vec3 TMPup = glm::vec3(0.0f, 1.0f, 0.0f);
        right = glm::normalize(glm::cross(TMPup, front));

        //Up axis
        up = glm::cross(front, right);
    }

    glm::mat4 calculateView() {
        return glm::lookAt(position, position + front, up);
    }

    void keyboardprocess(Movement movement, float deltaTime, float cameraSpeed) {
        switch(movement) {
            case FORWARD:
                position += glm::normalize(glm::vec3(front.x, 0, front.z)) * cameraSpeed * deltaTime;
                break;
            case BACKWARD:
                position -= glm::normalize(glm::vec3(front.x, 0, front.z)) * cameraSpeed * deltaTime;
                break;
            case LEFT:
                position += glm::normalize(right) * cameraSpeed * deltaTime;
                break;
            case RIGHT:
                position -= glm::normalize(right) * cameraSpeed * deltaTime;
                break;
            case UP:
                position.y += cameraSpeed * deltaTime;
                break;
            case DOWN:
                position.y -= cameraSpeed * deltaTime;
                break;
            default:
                break;
        }
    }

    

    void mouseprocess(float xoffset, float yoffset, GLboolean constrainPitch = true) {
        const float sensitivity = 0.1f;

        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;
    
        //euler xie
        if(constrainPitch) {
            if(pitch > 89.0f)
                pitch =  89.0f;
            if(pitch < -89.0f)
                pitch = -89.0f;
        }

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(direction);
    }
};