#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;


out vec4 FragColor;

uniform vec3 objectColor;  // fallback colore
uniform vec3 lightColor = vec3(1.0); // luce bianca
uniform vec3 lightDir = normalize(vec3(-0.5, -1.0, -0.3)); // luce direzionale
uniform vec3 viewPos;
uniform sampler2D texture_diffuse1; // Primo layer della texture


void main() {
    // Normalizzazione
    vec3 norm = normalize(Normal);
    vec3 light = normalize(-lightDir);

    // Diffuse
    float diff = max(dot(norm, light), 0.0);
    vec3 diffuse = diff * lightColor;

    // Ambient
    vec3 ambient = 0.2 * lightColor;

    // Specular (opzionale, puoi semplificare)
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-light, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = 0.3 * spec * lightColor;

    vec3 texColor = texture(texture_diffuse1, TexCoords).rgb;
    vec3 result = (ambient + diffuse + specular) * texColor;

    FragColor = vec4(result, 1.0);
}
