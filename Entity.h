#ifndef ENTITY_H
#define ENTITY_H

#include "auxiliary.h"

// Struttura per memorizzare i dati di un'entità
struct Entity {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int textureID;
    glm::vec3 position;
    glm::vec3 size;
    std::string texturePath;
};

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
    }

    stbi_image_free(data);

    return textureID;
}

// Funzione per creare e configurare un'entità
Entity createEntity(const float* vertices, size_t vertexCount, const std::string& texturePath, const glm::vec3& position, const glm::vec3& size) {
    Entity entity;
    entity.position = position;
    entity.size = size;
    entity.texturePath = texturePath;

    glGenVertexArrays(1, &entity.VAO);
    glGenBuffers(1, &entity.VBO);

    glBindVertexArray(entity.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, entity.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // Position
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Normal
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // Texture Coords
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    if (!texturePath.empty()) {
        entity.textureID = loadTexture(texturePath.c_str());
    }

    return entity;
}

// Funzione per disegnare un'entità
void drawEntity(const Entity& entity, Shader& shader, const glm::mat4& view, const glm::mat4& projection) {
    shader.use();
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, entity.position);
    model = glm::scale(model, entity.size);
    shader.setMat4("model", model);

    if (entity.textureID != 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, entity.textureID);
    }

    glBindVertexArray(entity.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

// Funzione per configurare il crosshair
void setupCrosshair(Entity& entity, float* vertices, size_t vertexSize) {
    glGenVertexArrays(1, &entity.VAO);
    glGenBuffers(1, &entity.VBO);
    glBindVertexArray(entity.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, entity.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// Funzione per configurare la hitbox
void setupHitbox(Entity& entity, float* vertices, size_t vertexSize, unsigned int* indices, size_t indexSize) {
    glGenVertexArrays(1, &entity.VAO);
    glGenBuffers(1, &entity.VBO);
    glGenBuffers(1, &entity.EBO);
    glBindVertexArray(entity.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, entity.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

// Funzione per configurare il testo
void setupText(Entity& entity) {
    glGenVertexArrays(1, &entity.VAO);
    glGenBuffers(1, &entity.VBO);
    glBindVertexArray(entity.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, entity.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void setupLight(Entity& entity) {

    glGenVertexArrays(1, &entity.VAO);
    glGenBuffers(1, &entity.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, entity.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubeLightVertices), CubeLightVertices, GL_STATIC_DRAW);
    glBindVertexArray(entity.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, entity.VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

#endif