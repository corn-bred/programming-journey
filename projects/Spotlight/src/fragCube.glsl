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
    sampler2D normalmap;
    sampler2D diffuseStrength;
    sampler2D specularStrength;
    sampler2D ambientStrength;

    float shininess;
    float bumpstrength;
};

uniform Material material;

struct LightPoint {
    vec3 position;
  
    vec3 ambientStrength;
    vec3 diffuseStrength;
    vec3 specularStrength;

    float constant;
    float linear;
    float quadratic;
};

struct LightSun {
    vec3 direction;
  
    vec3 ambientStrength;
    vec3 diffuseStrength;
    vec3 specularStrength;
};

struct LightSpotlight {
    vec3 position;
    vec3 direction;
    float innercutoff;
    float outercutoff;

    vec3 ambientStrength;
    vec3 diffuseStrength;
    vec3 specularStrength;

    float constant;
    float linear;
    float quadratic;
};

uniform LightSpotlight light;  

void main() {
    vec3 normalmapcol = texture(material.normalmap, TexCoords).rgb;

    vec3 norm = normalize( vec3(Normal.x + normalmapcol.r * 0, Normal.y + normalmapcol.g * 0, Normal.z + normalmapcol.b * 0) );//approximate but idc

    vec3 lightDir = normalize(lightPos - FragPos);  
    //vec3 lightDir = normalize(-light.direction);

    float theta = dot(lightDir, normalize(-light.direction)); 

    if(theta > light.outercutoff) {
        float dist = length(light.position - FragPos);
        float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * (dist*dist) );

        vec3 ambient = texture(material.ambientStrength, TexCoords).rgb * light.ambientStrength;

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * (light.diffuseStrength * texture(material.diffuseStrength, TexCoords).rgb);

        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = texture(material.specularStrength, TexCoords).rgb * spec * light.specularStrength;  
    
        //ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;

        float theta = dot(lightDir, normalize(-light.direction));
        float epsilon = light.innercutoff - light.outercutoff;
        float intensity = clamp((theta - light.outercutoff) / epsilon, 0.0, 1.0);

        diffuse *= intensity;
        specular *= intensity;

        vec3 result = (ambient+diffuse+specular);
        FragColor = vec4(result, 1.0);
    } else {
        FragColor = vec4(light.ambientStrength * texture(material.ambientStrength, TexCoords).rgb, 1.0);
    }
}