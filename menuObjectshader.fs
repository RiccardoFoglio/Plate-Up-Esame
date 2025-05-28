#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

// colore base o puoi passarlo come uniform se vuoi
uniform vec3 objectColor = vec3(1.0, 0.9, 0.8);

// luce direzionale base
uniform vec3 lightDir = normalize(vec3(-0.2f, -1.0f, -0.3f));
uniform vec3 lightColor = vec3(1.0);

void main() {
    // Normale normalizzata
    vec3 norm = normalize(Normal);

    // Diffuse lighting
    float diff = max(dot(norm, -lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = diffuse * objectColor;
    FragColor = vec4(result, 1.0);
}
