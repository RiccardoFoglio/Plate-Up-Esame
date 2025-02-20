#include "game_control.h"
#include <GLFW/glfw3.h>
#include <irrKlang.h>

// Inizializzazione dei vettori
glm::vec3 islandPosition = glm::vec3(0.0f, -0.5f, 0.0f);
glm::vec3 islandSize = glm::vec3(0.5f, 0.5f, 0.5f);
glm::vec3 fridgePosition = glm::vec3(-1.0f, -0.5f, 0.0f);
glm::vec3 fridgeSize = glm::vec3(0.5f, 0.5f, 0.5f);
glm::vec3 counterPosition = glm::vec3(1.0f, -0.5f, 4.0f);
glm::vec3 counterSize = glm::vec3(0.4f, 0.4f, 0.4f);

glm::vec3 islandPositionHitbox = glm::vec3(-0.1f, 0.0f, 0.05f);
glm::vec3 islandSizeHitbox = glm::vec3(1.6f, 1.0f, 3.0f);
glm::vec3 stovePositionHitbox = glm::vec3(-4.25f, 0.64f, 0.125f);
glm::vec3 stoveSizeHitbox = glm::vec3(0.32f, 0.1f, 0.5f);
glm::vec3 cutboardPositionHitbox = glm::vec3(-4.25f, 0.64f, 1.05f);
glm::vec3 cutboardSizeHitbox = glm::vec3(0.32f, 0.3f, 0.52f);
glm::vec3 sinkPositionHitbox = glm::vec3(-4.25f, 0.64f, -1.0f);
glm::vec3 sinkSizeHitbox = glm::vec3(0.42f, 0.3f, 0.52f);
glm::vec3 ovenPositionHitbox = glm::vec3(-4.25f, 0.95f, -3.1f);
glm::vec3 ovenSizeHitbox = glm::vec3(0.6f, 0.85f, 0.9f);
glm::vec3 fridgePositionHitbox = glm::vec3(-4.25f, 1.0f, -4.25f);
glm::vec3 fridgeSizeHitbox = glm::vec3(1.3f, 2.5f, 1.45f);
glm::vec3 counterPositionHitbox = glm::vec3(4.38f, 0.0f, -0.05f);
glm::vec3 counterSizeHitbox = glm::vec3(1.0f, 1.1f, 3.85f);

GameTimer::GameTimer(DifficultyLevel level) : level(level), gameOver(false) {
    setTimeForLevel(level);
}

void GameTimer::update(float deltaTime) {
    if (!gameOver && time > 0.0f) {
        time -= deltaTime;
        if (time <= 0.0f) {
            time = 0.0f;
            gameOver = true;
        }
    }
}

void GameTimer::reset() {
    setTimeForLevel(level);
    gameOver = false;
}

float GameTimer::getTime() const {
    return time;
}

bool GameTimer::isGameOver() const {
    return gameOver;
}

void GameTimer::nextLevel() {
    if (level == EASY) {
        level = MEDIUM;
    }
    else if (level == MEDIUM) {
        level = HARD;
    }
    reset();
}

void GameTimer::setTimeForLevel(DifficultyLevel level) {
    if (level == EASY) {
        time = 45.0f;
    }
    else if (level == MEDIUM) {
        time = 30.0f;
    }
    else if (level == HARD) {
        time = 20.0f;
    }
}

void checkHitboxSelections(Camera& camera, Inventory& inventory, irrklang::ISoundEngine* engine, GameTimer& timer) {
    glm::vec3 rayOrigin = camera.Position;
    glm::vec3 rayDirection = camera.Front;

    bool islandSelected = false;
    bool fridgeSelected = false;
    bool ovenSelected = false;
    bool cutboardSelected = false;
    bool counterSelected = false;

    //FRIDGE SELECTED
    if (rayIntersectsCuboid(rayOrigin, rayDirection, fridgePositionHitbox, fridgeSizeHitbox)) {
        fridgeSelected = true;
    }

    if (rayIntersectsCuboid(rayOrigin, rayDirection, fridgePositionHitbox, fridgeSizeHitbox)) {
        if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && fridgeSelected) {
            inventory.SetCarne(1);
            inventory.SetInsalata(1);
        }
    }

    //OVEN SELECTED
    if (rayIntersectsCuboid(rayOrigin, rayDirection, ovenPositionHitbox, ovenSizeHitbox)) {
        ovenSelected = true;
    }

    if (rayIntersectsCuboid(rayOrigin, rayDirection, ovenPositionHitbox, ovenSizeHitbox)) {
        if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && ovenSelected) {
            inventory.SetPane(1);
        }
    }

    //CUTBOARD SELECTED
    if (rayIntersectsCuboid(rayOrigin, rayDirection, cutboardPositionHitbox, cutboardSizeHitbox)) {
        cutboardSelected = true;
    }

    if (rayIntersectsCuboid(rayOrigin, rayDirection, cutboardPositionHitbox, cutboardSizeHitbox)) {
        if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && cutboardSelected) {
            inventory.SetPomodori(1);
        }
    }

    //COUNTER SELECTED
    if (rayIntersectsCuboid(rayOrigin, rayDirection, counterPositionHitbox, counterSizeHitbox)) {
        counterSelected = true;
    }

    if (rayIntersectsCuboid(rayOrigin, rayDirection, counterPositionHitbox, counterSizeHitbox)) {
        if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && counterSelected) {
            if (inventory.GetPane() == 1 && inventory.GetPomodori() == 1 && inventory.GetCarne() == 1 && inventory.GetInsalata() == 1) {
                inventory.SetPane(0);
                inventory.SetCarne(0);
                inventory.SetPomodori(0);
                inventory.SetInsalata(0);
                inventory.GetHamburger();
                inventory.SetHamburger(inventory.GetHamburger() + 1);
                engine->play2D("resources/media/bell.wav");
            }
        }
    }

    //ISLAND SELECTED
    if (rayIntersectsCuboid(rayOrigin, rayDirection, islandPositionHitbox, islandSizeHitbox)) {
        islandSelected = true;
    }

    if (rayIntersectsCuboid(rayOrigin, rayDirection, islandPositionHitbox, islandSizeHitbox)) {
        if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && islandSelected) {
            // Condizione specifica per il reset del timer e passaggio al livello successivo
            timer.nextLevel();
            engine->play2D("resources/media/bell.wav");
        }
    }
}
