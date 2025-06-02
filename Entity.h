#ifndef ENTITY_H
#define ENTITY_H

#include "auxiliary.h"
#include "globals.h"

struct Entity {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int textureID;
    glm::vec3 position;
    glm::vec3 size;
    std::string texturePath;
    int vertexCount;
};

unsigned int loadTexture(char const* path);

Entity createEntity(const float* vertices, size_t vertexCount, const std::string& texturePath, const glm::vec3& position, const glm::vec3& size);
void drawEntity(const Entity& entity, Shader& shader, const glm::mat4& view, const glm::mat4& projection);
void setupCrosshair(Entity& entity, float* vertices, size_t vertexSize);
void setupHitbox(Entity& entity, float* vertices, size_t vertexSize, unsigned int* indices, size_t indexSize);
void setupText(Entity& entity);
void setupLight(Entity& entity);

#endif
