#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material {
    sampler2D diffuse;
    sampler2D specularStrength;
    float shininess;
};

uniform Material material;

struct Light {
    vec3 position;
  
    vec3 ambientStrength;
    vec3 diffuseStrength;
    vec3 specularStrength;
};

uniform Light light;  

void main() {

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);  

    vec3 ambient = texture(material.diffuse, TexCoords).rgb * light.ambientStrength;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * (light.diffuseStrength * texture(material.diffuse, TexCoords).rgb);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = texture(material.specularStrength, TexCoords).rgb * spec * light.specularStrength;  

    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0);
}