#pragma once
#ifndef RENDER_SCENE_H
#define RENDER_SCENE_H

#include <vector>
#include "shader.h"
#include "Entity.h"
#include "Light.h"
#include "Recipe.h"

class RenderScene {
public:
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
        Entity& displayWall);

    void draw(const Recipe& currentRecipe);

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
};

#endif // RENDER_SCENE_H
