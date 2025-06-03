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
extern glm::vec3 padellaPosition, padellaSize;
extern glm::vec3 padellaPosition2;


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
    Model& tomato,
    Model& padella,
    Model& padella2)
    : objectShader(objectShader), lightCubeShader(lightCubeShader), projection(projection), crosshairShader(crosshairShader),
    textShader(textShader), wireframeShader(wireframeShader), plane(plane), walls(walls),
    crosshair(crosshair), textEntity(textEntity), hitbox(hitbox), lights(lights),
    lightCubeVAO(lightCubeVAO), displayWall(displayWall), island(island),
    fridgeBody(fridgeBody), fridgeDoor(fridgeDoor), counter(counter), ovenTop(ovenTop),
    ovenBottom(ovenBottom), burger(burger), cheese(cheese), egg(egg), tagliere(tagliere),
    insalata(insalata), bread(bread), ham(ham), trashBinBody(trashBinBody),
    trashBinTop(trashBinTop), tomato(tomato), padella(padella), padella2(padella2){}

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
    drawModelStatic(trashBinBody, trashBinBodyPosition, trashBinBodySize);
    drawModelStatic(trashBinTop, trashBinTopPosition, trashBinTopSize);
    drawModelStatic(fridgeBody, fridgePosition, fridgeSize);
	drawModelStatic(padella, padellaPosition, padellaSize);
    drawModelStatic(padella2, padellaPosition2, padellaSize);
    drawModelStatic(ovenBottom, ovenPosition, ovenSize);
    drawModelStatic(ovenTop, ovenTopPosition, ovenTopSize);
	drawModelStatic(tomato, tomatoPosition, tomatoSize);


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
 
    
    // === Crosshair ===
    crosshairShader.use();
    glBindVertexArray(crosshair.VAO);
    glDrawArrays(GL_LINES, 0, 4);

    // === Debug hitbox ===
	if (DEBUG) {
        glDisable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        wireframeShader.use();



        glm::vec3 objectPosition = cutboardPositionHitbox;
        glm::vec3 objectSize = cutboardSizeHitbox;


        // Set uniforms for the shader
        model = glm::mat4(1.0f);
        model = glm::translate(model, objectPosition); // Position of the hitbox
        model = glm::scale(model, objectSize);        // Size of the hitbox (matches the bounding box)

        wireframeShader.setMat4("model", model);
        wireframeShader.setMat4("view", view);
        wireframeShader.setMat4("projection", projection);
        wireframeShader.setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f)); // Red color

        glBindVertexArray(hitbox.VAO);
        glDrawElements(GL_LINES, hitboxIndicesCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_DEPTH_TEST);
    }
}


void RenderScene::drawUI(Points& score, GameTimer& timer, Inventory& inventory) {

	// === TIMER AND SCORE TEXT === //

    textShader.use();
    std::string timerText = "Timer: " + std::to_string(static_cast<int>(timer.getTime()));
    inventoryText.RenderText(textShader, timerText, 10.0f, SCR_HEIGHT - 30.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);

    textShader.use();
    std::string pointText = "Points: " + std::to_string(static_cast<int>(score.getPoints()));
    inventoryText.RenderText(textShader, pointText, 10.0f, SCR_HEIGHT - 60.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);

	// === INVENTORY TEXT === //
    // Enable blending for text rendering
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    textShader.use(); // Ensure text shader is active
       

    int ric = timer.getRicetta();
    inventoryText.RenderText(textShader, "Hamburger", SCR_WIDTH - 200.0f, SCR_HEIGHT - 60.0f, 0.5f, glm::vec3(0.3f, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
    std::string ric_string = std::to_string(ric);
    inventoryText.RenderText(textShader, ric_string, SCR_WIDTH - 200.0f, SCR_HEIGHT - 60.0f, 0.5f, glm::vec3(0.3f, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);

    if (inventory.GetPane() > 0)
        inventoryText.RenderText(textShader, "Pane", SCR_WIDTH - 200.0f, SCR_HEIGHT - 90.0f, 0.5f, glm::vec3(0.3f, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
    else
        inventoryText.RenderText(textShader, "Pane", SCR_WIDTH - 200.0f, SCR_HEIGHT - 90.0f, 0.5f, glm::vec3(0.9f, 0.2f, 0.2f), textEntity.VAO, textEntity.VBO);

    if (inventory.GetCarne() > 0)
        inventoryText.RenderText(textShader, "Carne", SCR_WIDTH - 200.0f, SCR_HEIGHT - 120.0f, 0.5f, glm::vec3(0.3f, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
    else
        inventoryText.RenderText(textShader, "Carne", SCR_WIDTH - 200.0f, SCR_HEIGHT - 120.0f, 0.5f, glm::vec3(0.9f, 0.2f, 0.2f), textEntity.VAO, textEntity.VBO);

    if (inventory.GetFormaggio() > 0)
        inventoryText.RenderText(textShader, "Formaggio", SCR_WIDTH - 200.0f, SCR_HEIGHT - 150.0f, 0.5f, glm::vec3(0.3f, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
    else
        inventoryText.RenderText(textShader, "Formaggio", SCR_WIDTH - 200.0f, SCR_HEIGHT - 150.0f, 0.5f, glm::vec3(0.9f, 0.2f, 0.2f), textEntity.VAO, textEntity.VBO);

    if (ric == 2 || ric == 3) {
        if (inventory.GetPomodori() > 0)
            inventoryText.RenderText(textShader, "Pomodori", SCR_WIDTH - 200.0f, SCR_HEIGHT - 200.0f, 0.5f, glm::vec3(0.3f, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
        else
            inventoryText.RenderText(textShader, "Pomodori", SCR_WIDTH - 200.0f, SCR_HEIGHT - 200.0f, 0.5f, glm::vec3(0.9f, 0.2f, 0.2f), textEntity.VAO, textEntity.VBO);

        if (inventory.GetInsalata() > 0)
            inventoryText.RenderText(textShader, "Insalata", SCR_WIDTH - 200.0f, SCR_HEIGHT - 230.0f, 0.5f, glm::vec3(0.3f, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
        else
            inventoryText.RenderText(textShader, "Insalata", SCR_WIDTH - 200.0f, SCR_HEIGHT - 230.0f, 0.5f, glm::vec3(0.9f, 0.2f, 0.2f), textEntity.VAO, textEntity.VBO);
    }
    if (ric == 3) {
        if (inventory.GetUovo() > 0)
            inventoryText.RenderText(textShader, "Uova", SCR_WIDTH - 200.0f, SCR_HEIGHT - 260.0f, 0.5f, glm::vec3(0.3f, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
        else
            inventoryText.RenderText(textShader, "Uova", SCR_WIDTH - 200.0f, SCR_HEIGHT - 260.0f, 0.5f, glm::vec3(0.9f, 0.2f, 0.2f), textEntity.VAO, textEntity.VBO);
    }

    inventoryText.RenderText(textShader, "LET'S MAKE:", SCR_WIDTH - 200.0f, SCR_HEIGHT - 30.0f, 0.75f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);

    // Disable blending after text rendering
    glDisable(GL_BLEND);


    glEnable(GL_DEPTH_TEST);
}

