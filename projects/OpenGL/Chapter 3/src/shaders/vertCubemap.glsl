#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main() {
    TexCoords = aPos;
    vec4 pos = projection * view* vec4(aPos, 1.0);
    gl_Position = pos.xyww; //since w is always 1.0, the depth buffer always knows that it's behind everything (Since depth values go from 0 (closest) to 1 (farthest))
}