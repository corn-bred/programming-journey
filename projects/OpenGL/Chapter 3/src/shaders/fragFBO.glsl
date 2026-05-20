#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform sampler2D depstenTexture;
uniform float aTime;

float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);
}

float random(float x) {
    return fract(sin(x) * 43758.5453123);
}

float snap(float value, float step) {
    return round(value / step) * step;
}

void main()
{
    
    float strength = 0.002;
    vec2 cent = vec2(0.5, 0.5);
    vec2 normTexCoords = vec2(TexCoords.x - cent.x, TexCoords.y - cent.y);
    float dist = abs(sqrt(pow((normTexCoords.x), 2) + pow((normTexCoords.y), 2)));
    float depth = texture(depstenTexture, TexCoords).r;
    float targetdepth = texture(depstenTexture, cent).r;
    float difference = abs(depth - targetdepth);
    
    /*vec3 Result;
    vec2 coord = normTexCoords + 0.5;
    Result.r = texture(screenTexture, coord).r;
    coord = vec2(clamp(normTexCoords.x * (1 - dist * strength) + 0.5, 0.0, 1.0),    clamp(normTexCoords.y * (1 - dist * strength) + 0.5, 0.0, 1.0)  );
    Result.g = texture(screenTexture, coord).g;
    coord = vec2(clamp(normTexCoords.x * (1 - dist * (strength *2)) + 0.5, 0.0, 1.0),    clamp(normTexCoords.y * (1 - dist * (strength *2)) + 0.5, 0.0, 1.0));
    Result.b = texture(screenTexture, coord).b;*/
    /*
    int xShiftRes = 250, blockRes = 15, crtRes = 250;

    vec3 Result;
    float strengthRand = strength / 10.0 + mod(random(aTime), strength);
    strengthRand += mod(random(snap((TexCoords.y + mod(random(aTime), 10.0)), 1 / float(xShiftRes) )), strength);

    float noise = random(TexCoords.xy + aTime) * 0.15 * (strength * 25);

    float crt = 0.9 + 0.1 * (1 - (sin(snap(TexCoords.y, crtRes)* 800.0) *strength) );

    vec2 block = floor(TexCoords * blockRes) / blockRes;

    vec2 coord = 
            vec2(clamp((TexCoords.x + random(block + aTime) * strength) - strengthRand, 0.0, 1.0), clamp((TexCoords.y + random(block + aTime) * strength), 0.0, 1.0));
    Result.r = (texture(screenTexture, coord).r + noise) *crt;
    coord = vec2(clamp((TexCoords.x + random(block + aTime) * strength) - strengthRand / 10.0, 0.0, 1.0), clamp((TexCoords.y + random(block + aTime) * strength), 0.0, 1.0));
    Result.g = (texture(screenTexture, coord).g + noise) *crt;
    coord = vec2(clamp((TexCoords.x + random(block + aTime) * strength) + strengthRand, 0.0, 1.0), clamp((TexCoords.y + random(block + aTime) * strength), 0.0, 1.0));
    Result.b = (texture(screenTexture, coord).b + noise) *crt;*/

    vec2 offsets[9] = vec2[](
        vec2(-strength,  strength), vec2( 0.0f,    strength), vec2( strength,  strength), 
        vec2(-strength,  0.0f),   vec2( 0.0f,    0.0f),   vec2( strength,  0.0f),   
        vec2(-strength, -strength), vec2( 0.0f,   -strength), vec2( strength, -strength)
    );

    float kernel[9] = float[]( //16, because 1 + 1 + 1 + 1 + 2 + 2 + 2 + 2 + 4 = 16
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16  
    );

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++) {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + ( offsets[i] *(difference * 10) ) ) );
    }

    vec3 Result;
    for (int i = 0; i < 9; i++) {
        Result += sampleTex[i] *kernel[i];
    }
    FragColor = vec4(Result, 1.0);
}