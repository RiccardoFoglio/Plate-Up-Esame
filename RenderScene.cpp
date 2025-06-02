#include "RenderScene.h"
#include "Text.h"
#include "camera.h"
#include "globals.h"
#include "Inventory.h"
#include "Recipe.h"
#include "Entity.h"
#include "Shader.h"
#include "Light.h"

extern Text inventoryText;
extern Camera camera;
extern float deltaTime;
extern  const bool DEBUG;
extern irrklang::ISoundEngine* engine;

extern glm::vec3 islandPosition, islandSize;
extern glm::vec3 fridgePosition, fridgeSize, fridgeDoorPosition;
extern glm::vec3 counterPosition, counterSize;
extern glm::vec3 ovenPosition, ovenSize;
extern glm::vec3 burgerPosition, burgerSize;
extern glm::vec3 cheesePosition, cheeseSize;
extern glm::vec3 eggPosition, eggSize;
extern glm::vec3 taglierePosition, tagliereSize;
extern glm::vec3 insalataPosition, insalataSize;
extern glm::vec3 breadPosition, breadSize;
extern glm::vec3 hamPosition, hamSize;
extern glm::vec3 trashBinBodyPosition, trashBinBodySize;
extern glm::vec3 trashBinTopPosition, trashBinTopSize;
extern glm::vec3 tomatoPosition, tomatoSize;


extern float currentFridgeDoorAngle;
extern void updateFridgeDoorAnimation(float deltaTime);
extern void checkHitboxSelections(Camera& camera, Inventory& inventory, irrklang::ISoundEngine* engine, GameTimer& timer, Points& score, const Recipe& recipe);


extern GameManager gameManager;

RenderScene::RenderScene(Shader& objectShader,
    Shader& lightCubeShader,
    glm::mat4& projection,
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
    Entity& displayWall,
    Model& island,
    Model& fridgeBody,
    Model& fridgeDoor,
    Model& counter,
    Model& ovenTop,
    Model& ovenBottom,
    Model& burger,
    Model& cheese,
    Model& egg,
    Model& tagliere,
    Model& insalata,
    Model& bread,
    Model& ham,
    Model& trashBinBody,
    Model& trashBinTop,
    Model& tomato)
    : objectShader(objectShader), lightCubeShader(lightCubeShader), projection(projection), crosshairShader(crosshairShader),
    textShader(textShader), wireframeShader(wireframeShader), plane(plane), walls(walls),
    crosshair(crosshair), textEntity(textEntity), hitbox(hitbox), lights(lights),
    lightCubeVAO(lightCubeVAO), displayWall(displayWall), island(island),
    fridgeBody(fridgeBody), fridgeDoor(fridgeDoor), counter(counter), ovenTop(ovenTop),
    ovenBottom(ovenBottom), burger(burger), cheese(cheese), egg(egg), tagliere(tagliere),
    insalata(insalata), bread(bread), ham(ham), trashBinBody(trashBinBody),
    trashBinTop(trashBinTop), tomato(tomato) {}

void RenderScene::draw(const Recipe& recipe) {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, plane.textureID);

    // set uniforms 
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.GetViewMatrix();
    projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    objectShader.use();
    objectShader.setMat4("view", view);
    objectShader.setMat4("projection", projection);
    objectShader.setVec3("viewPos", camera.Position);
    objectShader.setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));
    

   // === Lights ===
   // light properties
    objectShader.setInt("numLights", lights.size());
    for (int i = 0; i < lights.size(); ++i) {
        objectShader.setVec3("lights[" + std::to_string(i) + "].position", lights[i].position);
        objectShader.setVec3("lights[" + std::to_string(i) + "].color", lights[i].color);
        objectShader.setFloat("lights[" + std::to_string(i) + "].intensity", lights[i].intensity);
    }


    // render the lamp objects
    lightCubeShader.use();
    lightCubeShader.setMat4("projection", projection);
    lightCubeShader.setMat4("view", view);
    for (const auto& light : lights) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, light.position);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader.setMat4("model", model);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }


    /*
    lightShader.use();
    lightShader.setMat4("projection", projection);
    lightShader.setMat4("view", view);
    for (const auto& light : lights) {
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, light.position);
        lightModel = glm::scale(lightModel, glm::vec3(0.2f));
        lightShader.setMat4("model", lightModel);
        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    */

    glStencilMask(0x00);
    updateFridgeDoorAnimation(deltaTime);


    //Entities
    drawEntity(plane, objectShader, view, projection);
    drawEntity(displayWall, objectShader, view, projection);
	drawEntity(walls, objectShader, view, projection);




    // Lambda per modelli statici (senza rotazione)
    auto drawModelStatic = [&](Model& nomeModello, const glm::vec3& pos, const glm::vec3& scale) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        model = glm::scale(model, scale);
        objectShader.setMat4("model", model);
        objectShader.setVec3("objectColor", glm::vec3(1.0f));
        nomeModello.Draw(objectShader);
    };

    // === Static models ===
    drawModelStatic (island, islandPosition, islandSize);
    drawModelStatic(egg, eggPosition, eggSize);
    drawModelStatic(cheese, cheesePosition, cheeseSize);
    drawModelStatic(burger, burgerPosition, burgerSize);
    drawModelStatic(tagliere, taglierePosition, tagliereSize);
    drawModelStatic(insalata, insalataPosition, insalataSize);
    drawModelStatic(bread, breadPosition, breadSize);
    drawModelStatic(ham, hamPosition, hamSize);
    drawModelStatic(tomato, tomatoPosition, tomatoSize);
    drawModelStatic(trashBinBody, trashBinBodyPosition, trashBinBodySize);
    drawModelStatic(trashBinTop, trashBinTopPosition, trashBinTopSize);
    drawModelStatic(fridgeBody, fridgePosition, fridgeSize);
    //drawModelStatic(ovenBottom, ovenPosition, counterSize);
    //drawModelStatic(ovenTop, ovenPosition, counterSize);




    // === Fridge door with rotation ===
    updateFridgeDoorAnimation(deltaTime);
    glm::mat4 modelDoor = glm::mat4(1.0f);
    glm::vec3 pivotOffset = glm::vec3(0.25f, 0.0f, 0.0f);
    modelDoor = glm::translate(modelDoor, fridgeDoorPosition);
    modelDoor = glm::rotate(modelDoor, glm::radians(currentFridgeDoorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    modelDoor = glm::scale(modelDoor, fridgeSize);
    objectShader.setMat4("model", modelDoor);
    fridgeDoor.Draw(objectShader);

    // === Rotated models ===
    glm::mat4 modelMat;

    // Counter (90° Y)
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, counterPosition);
    modelMat = glm::rotate(modelMat, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMat = glm::scale(modelMat, counterSize);
    objectShader.setMat4("model", modelMat);
    counter.Draw(objectShader);

    
    // Oven Top (90° Y)
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, ovenPosition + glm::vec3(0.0f, 0.2f, 0.0f));
    modelMat = glm::rotate(modelMat, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMat = glm::scale(modelMat, counterSize);
    objectShader.setMat4("model", modelMat);
    ovenTop.Draw(objectShader);

    // Oven Bottom (90° Y)
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, ovenPosition);
    modelMat = glm::rotate(modelMat, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMat = glm::scale(modelMat, counterSize);
    objectShader.setMat4("model", modelMat);
    ovenBottom.Draw(objectShader);
    
    // === Crosshair ===
    crosshairShader.use();
    glBindVertexArray(crosshair.VAO);
    glDrawArrays(GL_LINES, 0, 4);

    // === Debug hitbox ===
   
    wireframeShader.use();
    glm::vec3 objectPosition = glm::vec3(4.38f, 0.0f, -0.05f);
    glm::vec3 objectSize = glm::vec3(1.0f, 1.1f, 3.85f);

    // Set uniforms for the shader
    model = glm::mat4(1.0f);
    model = glm::translate(model, objectPosition); // Position of the hitbox
    model = glm::scale(model, objectSize);        // Size of the hitbox (matches the bounding box)

    wireframeShader.setMat4("model", model);
    wireframeShader.setMat4("view", view);
    wireframeShader.setMat4("projection", projection);
    wireframeShader.setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f)); // Red color

    // Draw the edges of the bounding box
    glBindVertexArray(hitbox.VAO);
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
   
}


void RenderScene::drawUI(Points& score, GameTimer& timer, Inventory& inventory) {
    glDisable(GL_DEPTH_TEST);
    textShader.use();

    std::string timerText = "Timer: " + std::to_string(static_cast<int>(timer.getTime()));
    inventoryText.RenderText(textShader, timerText, 10.0f, SCR_HEIGHT - 30.0f, 0.5f,
        glm::vec3(0.3f, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);

    std::string pointText = "Points: " + std::to_string(static_cast<int>(score.getPoints()));
    inventoryText.RenderText(textShader, pointText, 10.0f, SCR_HEIGHT - 60.0f, 0.5f,
        glm::vec3(0.3f, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);

    if (inventory.GetState()) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        textShader.use();

        inventoryText.RenderText(textShader, "Ricetta attuale:", 600.0f, 410.0f, 0.6f,
            glm::vec3(1.0f, 0.85f, 0.2f), textEntity.VAO, textEntity.VBO);

        float y = 390.0f;
        float x = 610.0f;
        float scale = 0.5f;

        inventoryText.RenderText(textShader, gameManager.currentRecipe.getName(), x, y, scale,
            glm::vec3(0.9f, 0.9f, 0.9f), textEntity.VAO, textEntity.VBO);
        y -= 20.0f;

        for (const std::string& ingredient : gameManager.currentRecipe.getCurrentIngredients()) {
            inventoryText.RenderText(textShader, "- " + ingredient, x + 10.0f, y, scale,
                glm::vec3(0.8f, 0.8f, 0.8f), textEntity.VAO, textEntity.VBO);
            y -= 18.0f;
        }

        glDisable(GL_BLEND);
    }

    glEnable(GL_DEPTH_TEST);
}

