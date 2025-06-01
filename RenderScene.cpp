#include "RenderScene.h"
#include "Text.h"
#include "camera.h" // se usi camera globale

extern TextRenderer inventoryText; // se definito altrove
extern Camera camera;              // idem

RenderScene::RenderScene(Shader& objectShader,
    Shader& lightShader,
    Shader& crosshairShader,
    Shader& textShader,
    Shader& wireframeShader,
    Entity& plane,
    Entity& walls,
    Entity& crosshair,
    Entity& textEntity,
    Entity& hitbox,
    std::vector<Light>& lights,
    unsigned int lightCubeVAO,
    Entity& displayWall)
    : objectShader(objectShader),
    lightShader(lightShader),
    crosshairShader(crosshairShader),
    textShader(textShader),
    wireframeShader(wireframeShader),
    plane(plane),
    walls(walls),
    crosshair(crosshair),
    textEntity(textEntity),
    hitbox(hitbox),
    lights(lights),
    lightCubeVAO(lightCubeVAO),
    displayWall(displayWall) {}

void RenderScene::draw(const Recipe& currentRecipe) {
    // Setup matrices
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 1280.0f / 720.0f, 0.1f, 100.0f);

    // Use shader
    objectShader.use();
    objectShader.setMat4("view", view);
    objectShader.setMat4("projection", projection);
    objectShader.setVec3("viewPos", camera.Position);

    // Light uniforms
    objectShader.setInt("numLights", lights.size());
    for (int i = 0; i < lights.size(); ++i) {
        objectShader.setVec3("lights[" + std::to_string(i) + "].position", lights[i].position);
        objectShader.setVec3("lights[" + std::to_string(i) + "].color", lights[i].color);
        objectShader.setFloat("lights[" + std::to_string(i) + "].intensity", lights[i].intensity);
    }

    // Draw entities
    drawEntity(plane, objectShader, view, projection);
    drawEntity(displayWall, objectShader, view, projection);
    drawEntity(walls, objectShader, view, projection);

    // Draw lights
    lightShader.use();
    lightShader.setMat4("view", view);
    lightShader.setMat4("projection", projection);
    for (const auto& light : lights) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), light.position);
        model = glm::scale(model, glm::vec3(0.2f));
        lightShader.setMat4("model", model);
        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // Draw crosshair
    crosshairShader.use();
    glBindVertexArray(crosshair.VAO);
    glDrawArrays(GL_LINES, 0, 4);

    // Draw current recipe
    textShader.use();
    inventoryText.RenderText(textShader, "Ricetta: " + currentRecipe.getName(), 20.0f, 680.0f, 0.6f,
        glm::vec3(1.0f, 1.0f, 0.5f), textEntity.VAO, textEntity.VBO);

    float y = 660.0f;
    for (const auto& ing : currentRecipe.getRequiredIngredients()) {
        inventoryText.RenderText(textShader, "- " + ing, 40.0f, y, 0.45f,
            glm::vec3(0.8f, 0.8f, 0.8f), textEntity.VAO, textEntity.VBO);
        y
