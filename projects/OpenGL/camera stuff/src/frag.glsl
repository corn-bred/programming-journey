#version 330 core

out vec4 FragColor;

in vec2 texturecoord;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main() {
    FragColor = mix(texture(tex1, texturecoord), texture(tex2, texturecoord), 0.2);
}