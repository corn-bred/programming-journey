#version 330 core

in vec2 TexCoords;

out vec4 FragColor;
uniform sampler2D Texture;


void main() {
    vec4 texColor = texture(Texture, TexCoords);
    FragColor = texColor;
}