#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 objectColor;
uniform vec3 lightColor;
//uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material {
    sampler2D normalmap;
    sampler2D diffuseStrength;
    sampler2D specularStrength;
    sampler2D ambientStrength;

    
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_diffuse3;

    sampler2D texture_specular1;
    sampler2D texture_specular2;

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

#define NR_POINT_LIGHTS 4  
uniform LightPoint pointLights[NR_POINT_LIGHTS];

vec3 calculateLightPoint(LightPoint light, vec3 norm, vec3 FragPos, vec3 viewDir);

vec3 calculateLightSun(LightSun light, vec3 norm, vec3 viewDir);

vec3 calculateLightSpotlight(LightSpotlight light, vec3 norm, vec3 fragPos, vec3 viewDir);

uniform LightSun sun;
uniform LightSpotlight spotlight;


void main() {
    vec3 norm = normalize( Normal );

    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = calculateLightSun(sun, norm, viewDir);
    
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += calculateLightPoint(pointLights[i], norm, FragPos, viewDir);

    result += calculateLightSpotlight(spotlight, norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0f);  

    //vec3 lightDir = normalize(lightPos - FragPos);  
    //vec3 lightDir = normalize(-light.direction);

    /*float theta = dot(lightDir, normalize(-light.direction)); 

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
    }*/
}

vec3 calculateLightPoint(LightPoint light, vec3 norm, vec3 FragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - FragPos); 

    float dist = length(light.position - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * (dist*dist) );

    vec3 ambient = texture(material.ambientStrength, TexCoords).rgb * light.ambientStrength;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * (light.diffuseStrength * texture(material.diffuseStrength, TexCoords).rgb);

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = texture(material.specularStrength, TexCoords).rgb * spec * light.specularStrength;  
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = (ambient+diffuse+specular);
    return result;
}

vec3 calculateLightSun(LightSun light, vec3 norm, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

    vec3 ambient = texture(material.ambientStrength, TexCoords).rgb * light.ambientStrength;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * (light.diffuseStrength * texture(material.diffuseStrength, TexCoords).rgb);

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = texture(material.specularStrength, TexCoords).rgb * spec * light.specularStrength;  

    vec3 result = (ambient+diffuse+specular);
    return result;
}

vec3 calculateLightSpotlight(LightSpotlight light, vec3 norm, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

        float dist = length(light.position - FragPos);
        float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * (dist*dist) );

        vec3 ambient = texture(material.ambientStrength, TexCoords).rgb * light.ambientStrength;

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * (light.diffuseStrength * texture(material.diffuseStrength, TexCoords).rgb);

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
        return result;
}