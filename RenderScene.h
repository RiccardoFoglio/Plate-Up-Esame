#pragma once
#ifndef RENDER_SCENE_H
#define RENDER_SCENE_H

#include <vector>
#include "shader.h"
#include "Entity.h"
#include "Light.h"
#include "Recipe.h"
#include "Model.h"
#include "game_control.h"
#include "Inventory.h"
#include "recipe.h"


class RenderScene {
public:
    void draw(const Recipe& recipe);
    void drawEntity(Entity& entity, Shader& shader, glm::mat4& view, glm::mat4& projection);
    void drawUI(Points& score, GameTimer& timer, Inventory& inventory);


    RenderScene(Shader& objectShader,
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
        Model& tomato);

    
private:
    Shader& objectShader;
    Shader& lightShader;
    Shader& crosshairShader;
    Shader& textShader;
    Shader& wireframeShader;

    Entity& plane;
    Entity& walls;
    Entity& crosshair;
    Entity& textEntity;
    Entity& hitbox;
    Entity& displayWall;

    std::vector<Light>& lights;
    unsigned int lightCubeVAO;

    Model& island;
    Model& fridgeBody;
    Model& fridgeDoor;
    Model& counter;
    Model& ovenTop;
    Model& ovenBottom;
    Model& burger;
    Model& cheese;
    Model& egg;
    Model& tagliere;
    Model& insalata;
    Model& bread;
    Model& ham;
    Model& trashBinBody;
    Model& trashBinTop;
    Model& tomato;
};




#endif // RENDER_SCENE_H
