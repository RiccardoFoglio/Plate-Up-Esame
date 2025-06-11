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
#include "bonus_malus.h"
#include "recipe.h"


class RenderScene {
public:
    void draw(const Recipe& recipe);
    void drawUI(Points& score, GameTimer& timer, Inventory& inventory, Recipe& currentRecipe);

    unsigned int texture_panino0, texture_panino1, texture_panino2, texture_panino3;

    RenderScene(Shader& objectShader,
        Shader& lightCubeShader,
        glm::mat4& projection,
        Shader& crosshairShader,
        Shader& textShader,
        Shader& wireframeShader,
        Entity& plane,
        Entity& walls,
        Entity& ceiling,
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
        Model& bonusMalusCube
    );


    
private:
    Shader& objectShader;
    Shader& lightCubeShader;
    glm::mat4& projection;
    Shader& crosshairShader;
    Shader& textShader;
    Shader& wireframeShader;

    Entity& plane;
    Entity& walls;
    Entity& ceiling;
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
    Model& padella;
    Model& bonusMalusCube;
};




#endif // RENDER_SCENE_H
