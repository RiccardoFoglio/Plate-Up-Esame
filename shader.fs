#version 330 core
out vec4 FragColor;

in vec3 FragPos;  // From vertex shader
in vec3 Normal;   // From vertex shader
in vec2 TexCoords; // From vertex shader

uniform sampler2D texture_diffuse1;

struct Light {
    vec3 position;
    vec3 color;
    float intensity;
};

#define MAX_LIGHTS 10
uniform int numLights;
uniform Light lights[MAX_LIGHTS];

uniform vec3 viewPos;
uniform vec3 objectColor;   // Object's base color (optional if texture is used)

void main()
{    
    vec3 ambient = vec3(0.0f);
    vec3 diffuse = vec3(0.0f);
    vec3 specular = vec3(0.0f);

    for (int i = 0; i < numLights; ++i) {
        // Ambient lighting
        float ambientStrength = 0.1;
        ambient += ambientStrength * lights[i].color * lights[i].intensity;

        // Diffuse lighting
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lights[i].position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        diffuse += diff * lights[i].color * lights[i].intensity;

        // Specular lighting
        float specularStrength = 0.5;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        specular += specularStrength * spec * lights[i].color * lights[i].intensity;
    }

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = texture(texture_diffuse1, TexCoords) * vec4(result, 1.0);
}