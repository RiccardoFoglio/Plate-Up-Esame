#include "game_control.h"
#include <GLFW/glfw3.h>
#include <irrKlang.h>


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

// Posizioni e dimensioni degli oggetti relazionati al isola centrale
glm::vec3 burgerPosition = islandPosition;
glm::vec3 burgerSize = islandSize;
glm::vec3 cheesePosition = islandPosition;
glm::vec3 cheeseSize = islandSize;
glm::vec3 eggPosition = islandPosition;
glm::vec3 eggSize = islandSize;
glm::vec3 taglierePosition = islandPosition;
glm::vec3 tagliereSize = islandSize;
glm::vec3 insalataPosition = islandPosition;
glm::vec3 insalataSize = islandSize;
glm::vec3 breadPosition = islandPosition;
glm::vec3 breadSize = islandSize;
glm::vec3 hamPosition = islandPosition;
glm::vec3 hamSize = islandSize;
glm::vec3 tomatoPosition = islandPosition;
glm::vec3 tomatoSize = islandSize;

// Posizioni e dimensioni del bidone della spazzatura
glm::vec3 trashBinBodyPosition = islandPosition;
glm::vec3 trashBinBodySize = islandSize;
glm::vec3 trashBinTopPosition = islandPosition;
glm::vec3 trashBinTopSize = islandSize;

// Posizioni e dimensioni delle hitbox
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





GameTimer::GameTimer(GameLevel level) : level(level), gameOver(false) {
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
    if (level < LEVEL_3) {
        level = static_cast<GameLevel>(static_cast<int>(level) + 1);
    }
    reset();
}

void GameTimer::setTimeForLevel(GameLevel level) {
	switch(level) {
        case LEVEL_0: time = 90.0f; break;
		case LEVEL_1: time = 80.0f; break;
		case LEVEL_2: time = 70.0f; break;
		case LEVEL_3: time = 60.0f; break;
		default: time = 90.0f; // Default case
	}
}

// Classe per gestire i punti del gioco

Points::Points() : points(0) {}

void Points::resetPoints() {
	points = 0;
}

void Points::addPoints(int p) {
	points += p;
	if (points < 0) {
		points = 0; // Assicurati che i punti non diventino negativi
	}
}

void Points::removePoints(int p) {
    points -= p;
	if (points < 0) {
		points = 0; // Assicurati che i punti non diventino negativi
	}
}

int Points::getPoints() const {
    return points;
}


// Funzioni per gestire il passaggio di round e livelli

void GameManager::resetTransition() {
    isTransitioning = true;
    transitionCountdown = 3.0f;
}

bool GameManager::checkRoundPassed(const Points& score) const {
    return score.getPoints() >= sogliaPunti(level);
}

bool GameManager::checkVictory() const {
    return level == LEVEL_3 && round > maxRounds;
}

int GameManager::sogliaPunti(GameLevel level) const {
    switch (level) {
    case LEVEL_0: return 500;
    case LEVEL_1: return 1000;
    case LEVEL_2: return 1500;
    case LEVEL_3: return 2000;
    default: return 0; // Default case
    }
}

void GameManager::nextRound(Points& score) {
    round++;
    if (round > maxRounds) {
        level = static_cast<GameLevel>(static_cast<int>(level) + 1);
        round = 1;
    }
    resetTransition();
    score.resetPoints();
}


//Check tempo di pressione 

static double lastClickTime = 0.0;
const double clickCooldown = 0.5; // in secondi


void checkHitboxSelections(Camera& camera, Inventory& inventory, irrklang::ISoundEngine* engine, GameTimer& timer, Points& score, Recipe& GameManager.currentRecipe) {
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

                bool hasAllIngredients_recipe_0 =
                    inventory.GetPane() == 1 &&
                    inventory.GetPomodori() == 1 &&
                    inventory.GetCarne() == 1 &&
                    inventory.GetInsalata() == 1;

                inventory.SetPane(0);
                inventory.SetCarne(0);
                inventory.SetPomodori(0);
                inventory.SetInsalata(0);

                if (hasAllIngredients_recipe_0) {
                    inventory.SetHamburger(inventory.GetHamburger() + 1);
                    score.addPoints(100);
                    engine->play2D("resources/media/bell.wav");
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
            timer.nextLevel();
            engine->play2D("resources/media/bell.wav");
        }
    }
}
// Animazione della porta del frigorifero
bool isFridgeDoorOpen = false;
float currentFridgeDoorAngle = 0.0f;
float targetFridgeDoorAngle = 0.0f;
float fridgeDoorAnimationSpeed = 150.0f; // gradi al secondo

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
