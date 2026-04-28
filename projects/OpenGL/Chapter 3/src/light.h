#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class LightHandler {
    public:
    float constant, linear, quadratic;
    LightHandler(float Constant = 1.0f, int Linear = 0.09f, int Quadratic = 0.032f) : constant(Constant), linear(Linear), quadratic(Quadratic) {}
};