#include "game_control.h"
#include <GLFW/glfw3.h>
#include <irrKlang.h>
#include <cstdlib>
#include <ctime>
#include "globals.h"

#include <fstream>
#include <ctime>
#include <iomanip>

// Animazioni
bool isFridgeDoorOpen = false;

bool isFridgeDoorOpening = false;
bool isFridgeDoorClosing = false;
float fridgeOpenTimer = 0.0f;
float fridgeOpenDuration = 0.5f; // Durata dell'apertura della porta del frigorifero in secondi

float currentFridgeDoorAngle = 0.0f;
float targetFridgeDoorAngle = 0.0f;
float fridgeDoorAnimationSpeed = 150.0f; // gradi al secondo

// Input per il frigorifero
bool fridgeInputActive = false;
std::string fridgeInputText = "";

bool isTrashcanOpen = false;
float currentTrashcanLidAngle = 0.0f;
float targetTrashcanLidAngle = 0.0f;
float trashcanLidAnimationSpeed = 150.0f; // gradi al secondo

// booleano per disegnare il panino quando si completa la ricetta
bool drawHamburger = false;

bool drawBonusMalusCube = false;

extern BonusMalus bonusMalus;

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
glm::vec3 offsetHam = glm::vec3(0.0f, -0.5f, -0.5f);
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

// Function Definition
// ---------------------------------------------------------------------------------------------------------

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

void GameTimer::addTime(float t) {
    time += d;
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
// ---------------------------------------------------------------------------------------------------------

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
// ---------------------------------------------------------------------------------------------------------

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

    bonusMalus.isStartOfLevel = true;
    bonusMalus.resetCountBonusMalus();
    bonusMalus.resetNumBonusMalusActive();
    bonusMalus.setIsBonusMalusActive(false);
    bonusMalus.setIsBonusMalusPlaced(false);

    if (level < LEVEL_3 && round > 1) {
        level = getNextLevel(level);
        round = 1;
    }
    else if (level == LEVEL_3 && round > level3TotalRounds) {
        round = level3TotalRounds;
    }

    
	gameManager.totalScore += score.getPoints();

    resetTransition();
    score.resetPoints();
}

void GameManager::saveScoreRecord() {
    std::ofstream file("records.txt", std::ios::app);  // append mode
    if (!file.is_open()) return;

    // Ottieni data/ora corrente
    std::time_t now = std::time(nullptr);
    std::tm local;
    localtime_s(&local, &now);

    file << std::put_time(&local, "%Y-%m-%d %H:%M:%S") << " - " << totalScore << "\n";
    file.close();
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

    
    bool fridgeSelected = rayIntersectsCuboid(rayOrigin, rayDirection, fridgePositionHitbox, fridgeSizeHitbox) && distance(camera.Position, fridgePositionHitbox) < 4.0f;
    //bool insalataSelected = rayIntersectsCuboid(rayOrigin, rayDirection, insaltaPositionHitbox, insalataSizeHitbox);
    bool breadSelected = rayIntersectsCuboid(rayOrigin, rayDirection, breadPositionHitbox, breadSizeHitbox) && distance(camera.Position, breadPositionHitbox) < 3.0f;
    bool pomodoriSelected = rayIntersectsCuboid(rayOrigin, rayDirection, tomatoPositionHitbox, tomatoSizeHitbox) && distance(camera.Position, tomatoPositionHitbox) < 3.0f;
    bool cheeseSelected = rayIntersectsCuboid(rayOrigin, rayDirection, cheesePositionHitbox, cheeseSizeHitbox) && distance(camera.Position, cheesePositionHitbox) < 3.0f;
    //bool hamSelected = rayIntersectsCuboid(rayOrigin, rayDirection, hamPositionHitbox, hamSizeHitbox) && distance(camera.Position, hamPositionHitbox) < 3.0f;
    //bool eggSelected = rayIntersectsCuboid(rayOrigin, rayDirection, eggPositionHitbox, eggSizeHitbox) && distance(camera.Position, eggPositionHitbox) < 3.0f;
    bool islandSelected = rayIntersectsCuboid(rayOrigin, rayDirection, islandPositionHitbox, islandSizeHitbox) && distance(camera.Position, islandPositionHitbox) < 4.0f;
    bool trashSelected = rayIntersectsCuboid(rayOrigin, rayDirection, trashBinPositionHitbox, trashBinSizeHitbox) && distance(camera.Position, trashBinPositionHitbox) < 2.0f;
    bool counterSelected = rayIntersectsCuboid(rayOrigin, rayDirection, counterPositionHitbox, counterSizeHitbox) && distance(camera.Position, counterPositionHitbox) < 3.0f;

	// PIANO DI COTTURA
    bool padellaCarneSelected = rayIntersectsCuboid(rayOrigin, rayDirection, hamPositionHitbox, hamSizeHitbox);
    bool padellaUovoSelected = rayIntersectsCuboid(rayOrigin, rayDirection, eggPositionHitbox, eggSizeHitbox);

    // Verifico che il bonus attivo sia il numero 4, quello relativo agli ingredienti
    // just activated per attivare il bonus solo una volta
    if (bonusMalus.bonusMalusJustActivated && bonusMalus.getNumBonusMalusActive() == 4) {
        currentRecipe.addIngredient(inventory, currentRecipe);
    }

    //FRIDGE+INSALATA SELECTED
     if (clickedOnce && fridgeSelected){ 

        if (!isFridgeDoorOpening && !isFridgeDoorOpen && !isFridgeDoorClosing) {
            isFridgeDoorOpening = true;
            targetFridgeDoorAngle = -90.0f;
        }

        fridgeInputActive = true;
        fridgeInputText.clear();  // resetta il testo
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

    // === PADELLA_CARNE LOGIC ===

    static bool padellaCarneHeldLastFrame = false;
    bool padellaCarneHeld = padellaCarneSelected && mouseCurrentlyPressed;

    if (padellaCarneHeld && inventory.GetCarne() > 0) {
        if (!padellaCarneHeldLastFrame) {
            isLoading = true;
            loadingValue = 0.0f;
            showTargetZone = true;
            targetMin = 70.0f;
            targetMax = 85.0f;
        }

        loadingValue += deltaTime * 50.0f; // es. 2 secondi per caricare a 100
        loadingValue = std::min(100.0f, loadingValue);

    }
    else if (padellaCarneHeldLastFrame && !padellaCarneHeld && isLoading) {
        if (loadingValue >= targetMin && loadingValue <= targetMax) {
            inventory.SetCarne(0);
            inventory.SetCarneCotta(1); // oppure SetCotta(1)
            engine->play2D("resources/media/select.wav");
        }
        else {
            inventory.SetCarne(0); // bruciata
            engine->play2D("resources/media/error.wav");
        }

        isLoading = false;
        loadingValue = 0.0f;
        showTargetZone = false;
    }

    padellaCarneHeldLastFrame = padellaCarneHeld;


    // === PADELLA_UOVO LOGIC ===

    static bool padellaUovoHeldLastFrame = false;
    bool padellaUovoHeld = padellaUovoSelected && mouseCurrentlyPressed;

    if (padellaUovoHeld && inventory.GetUovo() > 0) {
        if (!padellaUovoHeldLastFrame) {
            isLoading = true;
            loadingValue = 0.0f;
            showTargetZone = true;
            targetMin = 60.0f;
            targetMax = 80.0f;
        }

        loadingValue += deltaTime * 50.0f;
        loadingValue = std::min(100.0f, loadingValue);
    }
    else if (padellaUovoHeldLastFrame && !padellaUovoHeld && isLoading) {
        if (loadingValue >= targetMin && loadingValue <= targetMax) {
            inventory.SetUovo(0);        // rimuove crudo
            inventory.SetUovoCotto(1);   // aggiunge cotto
            engine->play2D("resources/media/select.wav");
        }
        else {
            inventory.SetUovo(0); // bruciato
            engine->play2D("resources/media/error.wav");
        }

        isLoading = false;
        loadingValue = 0.0f;
        showTargetZone = false;
    }

    padellaUovoHeldLastFrame = padellaUovoHeld;

    //ISLAND SELECTED -- HAMBURGER MAKER
    if (clickedOnce && islandSelected){ 
        if (currentRecipe.isSatisfiedBy(inventory)) {

            inventory.SetHamburger(1);
            inventory.ClearInventoryAfterRecipeCompleted();

            if (inventory.GetHamburger() >= 1) {
                // mostra hamburger model
                drawHamburger = true;
            }   

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
        drawHamburger = false;
        engine->play2D("resources/media/trash.wav");
    }

    //DELIVERY SELECTED
    if (clickedOnce && counterSelected) {
        if (inventory.GetHamburger()) {

            // nascondi modello hamburger
            drawHamburger = false;
            
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

void gestioneBonusMalus(Camera& camera, GameLevel level, GameTimer timer, BonusMalus& bonusMalus) {
    if (bonusMalus.isStartOfLevel) {
        bonusMalus.timeStart = timer.getTime();
        bonusMalus.isStartOfLevel = false;
    }
    //verifica che il bonus / malus sia appena stato attivato
    else if (bonusMalus.bonusMalusJustActivated) {
        bonusMalus.timeStart = timer.getTime();
        bonusMalus.bonusMalusJustActivated = false;
        bonusMalus.setIsBonusMalusActive(true);
    }
    if (bonusMalus.getCountBonusMalus() == 1) {
        if (bonusMalus.playerIsOnBonusMalusCube(camera.Position, bonusMalus.getPositionBonusMalus())) {
            bonusMalus.enableRandom = true;
            bonusMalus.bonusMalusJustActivated = true;
            drawBonusMalusCube = false;
            bonusMalus.setIsBonusMalusActive(true);

            if (bonusMalus.enableRandom) {
                if (level == LEVEL_0 || level == LEVEL_1) {
                    bonusMalus.getRandomBonusMalus(2);
                }
                else if (level == LEVEL_2 || level == LEVEL_3) {
                    bonusMalus.getRandomBonusMalus(4);
                }
            }
            bonusMalus.enableRandom = false;

            bonusMalus.resetCountBonusMalus();

            bonusMalus.setIsBonusMalusPlaced(false);
        }
    }
    else if (bonusMalus.getCountBonusMalus() == 0 && bonusMalus.getIsBonusMalusActive()) {
        // disattiva il bonus / malus
        if (bonusMalus.timeStart - timer.getTime() >= 10.0f) {
            bonusMalus.setIsBonusMalusActive(false);
            bonusMalus.timeStart = timer.getTime();
        }
    }
    else {
        if (!bonusMalus.getIsBonusMalusActive()) {
            if (bonusMalus.timeStart - timer.getTime() >= 10.0f) {
                if (!bonusMalus.getIsBonusMalusPlaced()) {
                    bonusMalus.decidePositionCube(camera.Position);
                    bonusMalus.setIsBonusMalusPlaced(true);
                }
                bonusMalus.setCountBonusMalus();
                drawBonusMalusCube = true;
            }
        }
    }
}

void updateFridgeDoorAnimation(float deltaTime) {
    if (isFridgeDoorOpening) {
        currentFridgeDoorAngle -= fridgeDoorAnimationSpeed * deltaTime;
        if (currentFridgeDoorAngle <= -90.0f) {
            currentFridgeDoorAngle = -90.0f;
            isFridgeDoorOpening = false;
            isFridgeDoorOpen = true;
        }
    }
    else if (isFridgeDoorOpen) {
        // NON fare nulla mentre è aperto: resta aperto fino a input chiuso
        if (!fridgeInputActive) {
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

void processFridgeInput(std::string input, Inventory& inventory, const Recipe& recipe) {
    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) {
        return std::tolower(c);
        });

    bool valid = false;

    if (input == "carne" && (recipe.hasCarne() || recipe.hasCarneCotta() ) ) {
        inventory.SetCarne(1); valid = true;
    }
    else if (input == "formaggio" && recipe.hasFormaggio()) {
        inventory.SetFormaggio(1); valid = true;
    }
    else if (input == "pomodori" && recipe.hasPomodori()) {
        inventory.SetPomodori(1); valid = true;
    }
    else if (input == "insalata" && recipe.hasInsalata()) {
        inventory.SetInsalata(1); valid = true;
    }
    else if (input == "uovo" && (recipe.hasUovo() || recipe.hasUovoCotto()) ) {
        inventory.SetUovo(1); valid = true;
    }
}