#include "game_control.h"
#include <GLFW/glfw3.h>
#include <irrKlang.h>
#include <cstdlib>
#include <ctime>

// Animazioni
bool isFridgeDoorOpen = false;

bool isFridgeDoorOpening = false;
bool isFridgeDoorClosing = false;
float fridgeOpenTimer = 0.0f;
float fridgeOpenDuration = 0.5f; // Durata dell'apertura della porta del frigorifero in secondi

float currentFridgeDoorAngle = 0.0f;
float targetFridgeDoorAngle = 0.0f;
float fridgeDoorAnimationSpeed = 150.0f; // gradi al secondo

bool isTrashcanOpen = false;
float currentTrashcanLidAngle = 0.0f;
float targetTrashcanLidAngle = 0.0f;
float trashcanLidAnimationSpeed = 150.0f; // gradi al secondo

// Inizializzazione dei vettori
glm::vec3 islandPosition = glm::vec3(0.0f, -0.5f, 0.0f);
glm::vec3 islandSize = glm::vec3(0.5f, 0.5f, 0.5f);

glm::vec3 fridgePosition = glm::vec3(-1.0f, -0.5f, 0.0f);

glm::vec3 fridgeDoorPosition = glm::vec3(-3.8f, 1.6f, -3.6f);
glm::vec3 fridgeSize = glm::vec3(0.5f, 0.5f, 0.5f);

glm::vec3 counterPosition = glm::vec3(1.0f, -0.5f, 4.0f);
glm::vec3 counterSize = glm::vec3(0.4f, 0.4f, 0.4f);

glm::vec3 ovenTopPosition = glm::vec3(-4.7f, -0.5f, 0.0f);
glm::vec3 ovenTopSize = glm::vec3(0.4f, 0.4f, 0.4f);

glm::vec3 ovenPosition = glm::vec3(-4.7f, -0.5f, 0.0f);
glm::vec3 ovenSize = glm::vec3(0.4f, 0.4f, 0.4f);

// Posizioni e dimensioni degli oggetti relazionati al isola centrale
glm::vec3 burgerPosition = islandPosition;
glm::vec3 burgerSize = islandSize;

glm::vec3 insalataPosition = islandPosition + glm::vec3(-4.2f, 0.8f, -5.4f);
glm::vec3 insalataSize = islandSize;

// Posizioni e dimensioni degli oggetti relazionati all'oven 
glm::vec3 cheesePosition = ovenPosition;
glm::vec3 cheeseSize = ovenSize;

glm::vec3 taglierePosition = ovenPosition;
glm::vec3 tagliereSize = ovenSize; 

glm::vec3 padellaPosition = ovenPosition;
glm::vec3 padellaSize = ovenSize;
glm::vec3 padellaPosition2 = ovenPosition + glm::vec3(0.0f, 0.0f, -0.3f);

glm::vec3 eggPosition = ovenPosition;
glm::vec3 eggSize = ovenSize; 

glm::vec3 hamPosition = ovenPosition + glm::vec3(0.0f, 0.0f, 0.1f); 
glm::vec3 hamSize = ovenSize; 

glm::vec3 breadPosition = ovenPosition; 
glm::vec3 breadSize = ovenSize; 

glm::vec3 tomatoPosition = ovenPosition;
glm::vec3 tomatoSize = ovenSize;

// Posizioni e dimensioni del bidone della spazzatura
glm::vec3 trashBinBodyPosition = islandPosition;
glm::vec3 trashBinBodySize = islandSize;

glm::vec3 trashBinTopPosition = islandPosition + glm::vec3(-0.1f, 0.78f, -1.58f);
glm::vec3 trashBinTopSize = islandSize;

// Posizioni e dimensioni delle hitbox
glm::vec3 counterPositionHitbox = glm::vec3(4.38f, 0.0f, -0.05f);
glm::vec3 counterSizeHitbox = glm::vec3(1.0f, 1.1f, 3.85f);

glm::vec3 fridgePositionHitbox = glm::vec3(-4.25f, 1.0f, -4.25f);
glm::vec3 fridgeSizeHitbox = glm::vec3(1.3f, 2.5f, 1.45f);

glm::vec3 insaltaPositionHitbox = glm::vec3(-4.2f, 1.33f, -4.0f);
glm::vec3 insalataSizeHitbox = glm::vec3(0.4f, 0.3f, 0.4f);

glm::vec3 islandPositionHitbox = glm::vec3(-0.1f, 0.0f, 0.05f);
glm::vec3 islandSizeHitbox = glm::vec3(1.6f, 1.0f, 3.0f);

glm::vec3 hamPositionHitbox = glm::vec3(-4.55f, 0.64f, 0.8f);
glm::vec3 hamSizeHitbox = glm::vec3(0.7f, 0.1f, 0.35f);

glm::vec3 eggPositionHitbox = glm::vec3(-4.55f, 0.64f, 1.10);
glm::vec3 eggSizeHitbox = glm::vec3(0.7f, 0.1f, 0.35f);

// sinistra di stove
glm::vec3 cheesePositionHitbox = glm::vec3(-4.55f, 0.64f, 1.85f);
glm::vec3 cheeseSizeHitbox = glm::vec3(0.4f, 0.1f, 0.4f);

// destra di stove
glm::vec3 cutboardPositionHitbox = glm::vec3(-4.55f, 0.64f, -0.8f);
glm::vec3 cutboardSizeHitbox = glm::vec3(0.4f, 0.1f, 0.4f);

glm::vec3 tomatoPositionHitbox = glm::vec3(-4.55f, 0.64f, -0.85f);
glm::vec3 tomatoSizeHitbox = glm::vec3(0.4f, 0.1f, 0.4f);

glm::vec3 breadPositionHitbox = glm::vec3(-4.55f, 0.64f, 0.1f);
glm::vec3 breadSizeHitbox = glm::vec3(0.4f, 0.1f, 0.4f);

glm::vec3 ovenPositionHitbox = glm::vec3(-4.25f, 0.0f, 0.4f);
glm::vec3 ovenSizeHitbox = glm::vec3(0.6f, 0.85f, 0.9f);

glm::vec3 trashBinPositionHitbox = glm::vec3(-0.1f, 0.0f, -1.9f);
glm::vec3 trashBinSizeHitbox = glm::vec3(0.5f, 1.0f, 0.5f);



float getTimeForLevel(GameLevel level) {
    switch (level) {
    case LEVEL_0: return 90.0f;
    case LEVEL_1: return 75.0f;
    case LEVEL_2: return 60.0f;
    case LEVEL_3: return 45.0f;
    default: return 90.0f;
    }
}

int getPointsThresholdForLevel(GameLevel level) {
    switch (level) {
    case LEVEL_0: return 500;
    case LEVEL_1: return 1000;
    case LEVEL_2: return 1500;
    case LEVEL_3: return 2000;
    default: return 0;
    }
}

GameLevel getNextLevel(GameLevel current) {
    switch (current) {
    case LEVEL_0: return LEVEL_1;
    case LEVEL_1: return LEVEL_2;
    case LEVEL_2: return LEVEL_3;
    case LEVEL_3: return LEVEL_3; // massimo raggiunto
    default: return LEVEL_0;
    }
}

GameTimer::GameTimer(GameLevel level)
    : level(level), gameOver(false) {
    setTimeForLevel(level);
}

void GameTimer::setTimeForLevel(GameLevel level) {
	time = getTimeForLevel(level);
}

void GameTimer::update(float deltaTime) {
    if (gameOver) return;

    time -= deltaTime;
    if (time <= 0.0f) {
        time = 0.0f;
        gameOver = true;
    }
}

void GameTimer::reset() {
	gameOver = false;
	setTimeForLevel(level);
}

float GameTimer::getTime() const {
	return time;
}

void GameTimer::setLevel(GameLevel newLevel) {
	level = newLevel;
	setTimeForLevel(level);
}

GameLevel GameTimer::getLevel() {
	return level;
}   

bool GameTimer::isGameOver() const {
    return gameOver;
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
    return level == LEVEL_3 && round == level3TotalRounds;
}

int GameManager::sogliaPunti(GameLevel level) const {
	return getPointsThresholdForLevel(level);
}

void GameManager::nextRound(Points& score) {
    round++;

    if (level < LEVEL_3 && round > maxRounds) {
        level = getNextLevel(level);
        round = 1;
    }
    else if (level == LEVEL_3 && round > level3TotalRounds) {
        // Rimani su LEVEL_3, ma ferma a 5 round
        round = level3TotalRounds; // Forza il valore massimo
    }

    resetTransition();
    score.resetPoints();
}

float distance(glm::vec3 Pos1, glm::vec3 Pos2) {
    return sqrt((Pos1.x - Pos2.x) * (Pos1.x - Pos2.x) + (Pos1.z - Pos2.z) * (Pos1.z - Pos2.z));
}

void checkHitboxSelections(Camera& camera, Inventory& inventory, irrklang::ISoundEngine* engine, GameTimer& timer, Points& score, Recipe& currentRecipe) {
    glm::vec3 rayOrigin = camera.Position;
    glm::vec3 rayDirection = camera.Front;

	static bool mousePressedLastFrame = false;
	bool mouseCurrentlyPressed = glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
	bool clickedOnce = mouseCurrentlyPressed && !mousePressedLastFrame; 
	mousePressedLastFrame = mouseCurrentlyPressed;

    
    bool fridgeSelected = rayIntersectsCuboid(rayOrigin, rayDirection, fridgePositionHitbox, fridgeSizeHitbox)
            && distance(camera.Position, fridgePositionHitbox) < 4.0f;
    bool insalataSelected = rayIntersectsCuboid(rayOrigin, rayDirection, insaltaPositionHitbox, insalataSizeHitbox);
    bool breadSelected = rayIntersectsCuboid(rayOrigin, rayDirection, breadPositionHitbox, breadSizeHitbox)
            && distance(camera.Position, breadPositionHitbox) < 3.0f;
    bool pomodoriSelected = rayIntersectsCuboid(rayOrigin, rayDirection, tomatoPositionHitbox, tomatoSizeHitbox)
            && distance(camera.Position, tomatoPositionHitbox) < 3.0f;
    bool cheeseSelected = rayIntersectsCuboid(rayOrigin, rayDirection, cheesePositionHitbox, cheeseSizeHitbox)
            && distance(camera.Position, cheesePositionHitbox) < 3.0f;
    bool hamSelected = rayIntersectsCuboid(rayOrigin, rayDirection, hamPositionHitbox, hamSizeHitbox)
            && distance(camera.Position, hamPositionHitbox) < 3.0f;
    bool eggSelected = rayIntersectsCuboid(rayOrigin, rayDirection, eggPositionHitbox, eggSizeHitbox)
            && distance(camera.Position, eggPositionHitbox) < 3.0f;
    bool islandSelected = rayIntersectsCuboid(rayOrigin, rayDirection, islandPositionHitbox, islandSizeHitbox)
            && distance(camera.Position, islandPositionHitbox) < 4.0f;
    bool trashSelected = rayIntersectsCuboid(rayOrigin, rayDirection, trashBinPositionHitbox, trashBinSizeHitbox)
            && distance(camera.Position, trashBinPositionHitbox) < 3.0f;
    bool counterSelected = rayIntersectsCuboid(rayOrigin, rayDirection, counterPositionHitbox, counterSizeHitbox)
            && distance(camera.Position, counterPositionHitbox) < 3.0f;


    //FRIDGE+INSALATA SELECTED
     if (clickedOnce && fridgeSelected){ 

        /*
        // Animazione anta
        if (currentFridgeDoorAngle == targetFridgeDoorAngle) {
            isFridgeDoorOpen = !isFridgeDoorOpen;
            targetFridgeDoorAngle = isFridgeDoorOpen ? -90.0f : 0.0f;
        }
        if (insalataSelected && isFridgeDoorOpen) {
            // Controlla se salad è richiesta nella ricetta
            if (currentRecipe.hasInsalata()) {
                inventory.SetInsalata(1);
            }
            else {
                score.removePoints(50);
            }
        }
        */

         if (!isFridgeDoorOpening && !isFridgeDoorOpen && !isFridgeDoorClosing) {
             isFridgeDoorOpening = true;
             targetFridgeDoorAngle = -90.0f;
         }

         if (currentRecipe.hasInsalata()) {
             inventory.SetInsalata(1);
             engine->play2D("resources/media/select.wav");
         }
         else {
             engine->play2D("resources/media/error.wav");
             score.removePoints(50);
         }


    }
    
    //BREAD SELECTED
    if (clickedOnce && breadSelected) {
        if (currentRecipe.hasPane()) {
            inventory.SetPane(1);
            
            engine->play2D("resources/media/select.wav");
        }
        else {
			engine->play2D("resources/media/error.wav");
            score.removePoints(50);  // Penalità per ingrediente sbagliato
        }  
    }

    //POMODORI SELECTED
    if (clickedOnce && pomodoriSelected) {
        if (currentRecipe.hasPomodori()) {
            inventory.SetPomodori(1);
            engine->play2D("resources/media/select.wav");
        }
        else {
			engine->play2D("resources/media/error.wav");
            score.removePoints(50);  // Penalità per ingrediente sbagliato
        } 
    }

    //FORMAGGIO SELECTED
    if (clickedOnce && cheeseSelected) {
        if (currentRecipe.hasFormaggio()) {
            inventory.SetFormaggio(1);
            engine->play2D("resources/media/select.wav");
        }
        else {
			engine->play2D("resources/media/error.wav");
            score.removePoints(50);
        }
    }   

    // HAM SELECTED
    if (clickedOnce && hamSelected) {
        if (currentRecipe.hasCarne()) {
            inventory.SetCarne(1);
            engine->play2D("resources/media/select.wav");
        }
        else {
			engine->play2D("resources/media/error.wav");
            score.removePoints(50);
        }
    }

    // UOVO SELECTED
    if (clickedOnce && eggSelected) {
        if (currentRecipe.hasUovo()) {
            inventory.SetUovo(1);
            engine->play2D("resources/media/select.wav");
        }
        else {
			engine->play2D("resources/media/error.wav");
            score.removePoints(50);  // Penalità per ingrediente sbagliato
        }
    }

    //ISLAND SELECTED -- HAMBURGER MAKER
    if (clickedOnce && islandSelected){ 
        if (currentRecipe.isSatisfiedBy(inventory)) {

            inventory.SetHamburger(1);
            inventory.ClearInventoryAfterRecipeCompleted();

            // mostra hamburger model
            //
            //
            //
            //
            //
            //

            engine->play2D("resources/media/bell.wav");
        }
        else {
			engine->play2D("resources/media/error.wav");
            score.removePoints(50);
        }
    }

    // TRASH BIN SELECTED
    if (clickedOnce && trashSelected) {

        isTrashcanOpen = true;
		targetTrashcanLidAngle = 90.0f;
        inventory.ClearInventory();
        engine->play2D("resources/media/trash.wav");
    }

    //DELIVERY SELECTED
    if (clickedOnce && counterSelected) {
        if (inventory.GetHamburger()) {

            // nascondi modello hamburger
            //
            //
            //
            //
            //

            inventory.ClearInventory();
            score.addPoints(200);
            engine->play2D("resources/media/success.wav");
            currentRecipe = Recipe::getRandomRecipe(gameManager.level);
        }
        else {
			engine->play2D("resources/media/error.wav");
            score.removePoints(100);
        }

        // check next level
		if (gameManager.checkRoundPassed(score)) {
			gameManager.nextRound(score);
			timer.reset();
            engine->play2D("resources/media/livello_superato.wav");
		}

    }

}

void updateFridgeDoorAnimation(float deltaTime) {
    
    /*
    if (currentFridgeDoorAngle != targetFridgeDoorAngle) {
        float dir = (targetFridgeDoorAngle > currentFridgeDoorAngle) ? 1.0f : -1.0f;
        currentFridgeDoorAngle += dir * fridgeDoorAnimationSpeed * deltaTime;

        // Clamp
        if ((dir > 0 && currentFridgeDoorAngle > targetFridgeDoorAngle) ||
            (dir < 0 && currentFridgeDoorAngle < targetFridgeDoorAngle)) {
            currentFridgeDoorAngle = targetFridgeDoorAngle;
        }
    }
    */

    if (isFridgeDoorOpening) {
        currentFridgeDoorAngle -= fridgeDoorAnimationSpeed * deltaTime;
        if (currentFridgeDoorAngle <= -90.0f) {
            currentFridgeDoorAngle = -90.0f;
            isFridgeDoorOpening = false;
            isFridgeDoorOpen = true;
            fridgeOpenTimer = 0.0f;
        }
    }
    else if (isFridgeDoorOpen) {
        fridgeOpenTimer += deltaTime;
        if (fridgeOpenTimer >= fridgeOpenDuration) {
            isFridgeDoorOpen = false;
            isFridgeDoorClosing = true;
            targetFridgeDoorAngle = 0.0f;
        }
    }
    else if (isFridgeDoorClosing) {
        currentFridgeDoorAngle += fridgeDoorAnimationSpeed * deltaTime;
        if (currentFridgeDoorAngle >= 0.0f) {
            currentFridgeDoorAngle = 0.0f;
            isFridgeDoorClosing = false;
        }
    }

}

void updateTrashcanLidAnimation(float deltaTime) {
    if (currentTrashcanLidAngle != targetTrashcanLidAngle) {
        float dir = (targetTrashcanLidAngle > currentTrashcanLidAngle) ? 1.0f : -1.0f;
        currentTrashcanLidAngle += dir * trashcanLidAnimationSpeed * deltaTime;

        // Clamp
        if ((dir > 0 && currentTrashcanLidAngle > targetTrashcanLidAngle) ||
            (dir < 0 && currentTrashcanLidAngle < targetTrashcanLidAngle)) {
            currentTrashcanLidAngle = targetTrashcanLidAngle;

            // Se ha finito di aprirsi, svuota inventario e chiudi
            if (isTrashcanOpen && currentTrashcanLidAngle == 90.0f) {
                targetTrashcanLidAngle = 0.0f;
            }
            // Se ha finito di chiudersi, resetta stato
            else if (currentTrashcanLidAngle == 0.0f) {
                isTrashcanOpen = false;
            }
        }
    }
}
