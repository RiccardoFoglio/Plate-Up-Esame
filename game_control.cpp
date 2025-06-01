#include "game_control.h"
#include <GLFW/glfw3.h>
#include <irrKlang.h>
#include <cstdlib>
#include <ctime>

// Inizializzazione dei vettori
glm::vec3 islandPosition = glm::vec3(0.0f, -0.5f, 0.0f);
glm::vec3 islandSize = glm::vec3(0.5f, 0.5f, 0.5f);

glm::vec3 fridgePosition = glm::vec3(-1.0f, -0.5f, 0.0f);

glm::vec3 fridgeDoorPosition = glm::vec3(-3.8f, 1.6f, -3.6f);

glm::vec3 fridgeSize = glm::vec3(0.5f, 0.5f, 0.5f);

glm::vec3 counterPosition = glm::vec3(1.0f, -0.5f, 4.0f);
glm::vec3 counterSize = glm::vec3(0.4f, 0.4f, 0.4f);

glm::vec3 ovenPosition = glm::vec3(-4.7f, -0.5f, 0.0f);
glm::vec3 ovenSize = glm::vec3(2.0f, 2.0f, 2.0f);


glm::vec3 burgerPosition = glm::vec3(0.0f, -0.5f, 0.0f);
glm::vec3 burgerSize = glm::vec3(0.5f, 0.5f, 0.5f);


glm::vec3 cheesePosition = glm::vec3(0.0f, -0.5f, 0.0f);
glm::vec3 cheeseSize = glm::vec3(0.5f, 0.5f, 0.5f);

glm::vec3 eggPosition = glm::vec3(0.0f, -0.5f, 0.0f);
glm::vec3 eggSize = glm::vec3(0.5f, 0.5f, 0.5f);

glm::vec3 taglierePosition = glm::vec3(0.0f, -0.5f, 0.0f);
glm::vec3 tagliereSize = glm::vec3(0.5f, 0.5f, 0.5f);

glm::vec3 insalataPosition = glm::vec3(0.0f, -0.5f, 0.0f);
glm::vec3 insalataSize = glm::vec3(0.5f, 0.5f, 0.5f);

glm::vec3 breadPosition = glm::vec3(0.0f, -0.5f, 0.0f);
glm::vec3 breadSize = glm::vec3(0.5f, 0.5f, 0.5f);

glm::vec3 hamPosition = glm::vec3(0.0f, -0.5f, 0.0f);
glm::vec3 hamSize = glm::vec3(0.5f, 0.5f, 0.5f);

glm::vec3 tomatoPosition = glm::vec3(0.0f, -0.5f, 0.0f);
glm::vec3 tomatoSize = glm::vec3(0.5f, 0.5f, 0.5f);



glm::vec3 trashBinBodyPosition = glm::vec3(0.0f, -0.5f, 0.0f);
glm::vec3 trashBinBodySize = glm::vec3(0.5f, 0.5f, 0.5f);


glm::vec3 trashBinTopPosition = glm::vec3(0.0f, -0.5f, 0.0f);
glm::vec3 trashBinTopSize = glm::vec3(0.5f, 0.5f, 0.5f);

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



glm::vec3 burgerPositionHitbox = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 burgerSizeHitbox = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cheesePositionHitbox = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cheeseSizeHitbox = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 eggPositionHitbox = glm::vec3(-0.1f, 0.0f, 0.05f);
glm::vec3 eggSizeHitbox = glm::vec3(1.6f, 1.0f, 3.0f);
glm::vec3 taglierePositionHitbox = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 tagliereSizeHitbox = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 insaltaPositionHitbox = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 insalataSizeHitbox = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 breadPositionHitbox = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 breadSizeHitbox = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 hamPositionHitbox = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 hamSizeHitbox = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 tomatoPositionHitbox = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 tomatoSizeHitbox = glm::vec3(0.0f, 0.0f, 0.0f);


glm::vec3 trashBinTopPositionHitbox = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 trashBinTopSizeHitbox = glm::vec3(0.0f, 0.0f, 0.0f);


int ricetta = 0;


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

bool GameTimer::checkRecipe(Inventory &i, int r) {
    if (r == 1 && i.GetCarne() >= 1 && i.GetPane() >= 1 && i.GetFormaggio() >= 1)
        return true;
    else if (r == 2 && i.GetCarne() >= 1 && i.GetPane() >= 1 && i.GetFormaggio() >= 1
        && i.GetInsalata() >= 1 && i.GetPomodori() >= 1)
        return true;
    else if (r == 3 && i.GetCarne() >= 1 && i.GetPane() >= 1 && i.GetFormaggio() >= 1
        && i.GetInsalata() >= 1 && i.GetPomodori() >= 1 && i.GetUova() >= 1)
        return true;
    return false;
}

void GameTimer::setRicetta(int prevR, DifficultyLevel level) {
    srand(std::time(NULL));
    if (level == EASY) {
        if (prevR == 0)
            ricetta = 1;
        else {
            ricetta = std::rand() % 2 + 1; //ricetta 1 o 2
        }
    }
    else if (level == MEDIUM) {
        ricetta = std::rand() % 3 + 1; //ricetta 1 o 2 o 3
    }
    else if (level == HARD) {
        ricetta = std::rand() % 2 + 2; //ricetta 2 o 3
    }
}

int GameTimer::getRicetta() {
    return ricetta;
}

DifficultyLevel GameTimer::getLevel() {
    return this->level;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool isFridgeDoorOpen = false;
float currentFridgeDoorAngle = 0.0f;
float targetFridgeDoorAngle = 0.0f;
float fridgeDoorAnimationSpeed = 150.0f; // gradi al secondo



Points::Points() : points(0) {}


void Points::resetPoints() {
	points = 0;
}

void Points::addPoints(int p) {
	points += p;
}

void Points::removePoints(int p) {
    points -= p;
}

int Points::getPoints() const {
    return points;
}

int Points::pointsRequirednextLevel(DifficultyLevel level) {
    if (level == EASY)
        return 150;
    else if (level == MEDIUM)
        return 200;
    return 250; // HARD
}

//Check tempo di pressione 

static double lastClickTime = 0.0;
const double clickCooldown = 0.5; // in secondi





void checkHitboxSelections(Camera& camera, Inventory& inventory, irrklang::ISoundEngine* engine, GameTimer& timer, Points& score) {
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
            

            // Animazione anta
            if (currentFridgeDoorAngle == targetFridgeDoorAngle) {
                isFridgeDoorOpen = !isFridgeDoorOpen;
                targetFridgeDoorAngle = isFridgeDoorOpen ? -90.0f : 0.0f;
            }
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

            double currentTime = glfwGetTime();
            if (currentTime - lastClickTime >= clickCooldown) {
                lastClickTime = currentTime;

                bool hasAllIngredients_recipe = timer.checkRecipe(inventory, ricetta);

                /*inventory.SetPane(0);
                inventory.SetCarne(0);
                inventory.SetPomodori(0);
                inventory.SetInsalata(0);*/

                if (hasAllIngredients_recipe) {
                    inventory.ClearInventoryAfterRecipeCompleted();
                    inventory.SetHamburger(inventory.GetHamburger() + 1);
                    score.addPoints(100);
                    engine->play2D("resources/media/bell.wav");
                    timer.setRicetta(ricetta, timer.getLevel());
                }
                else {
                    if (score.getPoints() <= 0) {
                        score.resetPoints();
                    }
                    else {
                        score.removePoints(50);
                    }
                }
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
            if (score.getPoints() >= score.pointsRequirednextLevel(timer.getLevel())) {
                timer.nextLevel();
                engine->play2D("resources/media/bell.wav");
            }
        }
    }
}

void updateFridgeDoorAnimation(float deltaTime) {
    if (currentFridgeDoorAngle != targetFridgeDoorAngle) {
        float dir = (targetFridgeDoorAngle > currentFridgeDoorAngle) ? 1.0f : -1.0f;
        currentFridgeDoorAngle += dir * fridgeDoorAnimationSpeed * deltaTime;

        // Clamp
        if ((dir > 0 && currentFridgeDoorAngle > targetFridgeDoorAngle) ||
            (dir < 0 && currentFridgeDoorAngle < targetFridgeDoorAngle)) {
            currentFridgeDoorAngle = targetFridgeDoorAngle;
        }
    }
}
