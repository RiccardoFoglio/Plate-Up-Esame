#ifndef GAME_CONTROL_H
#define GAME_CONTROL_H

#include <glm/glm.hpp>
#include <vector>
#include "camera.h"
#include "inventory.h"
#include "object_selection.h"
#include "recipe.h"
#include <irrKlang.h>
#include <cstdlib>
#include <ctime>



// Vettori per le posizioni e le dimensioni delle hitbox
extern glm::vec3 islandPosition;
extern glm::vec3 islandSize;
extern glm::vec3 fridgePosition;
extern glm::vec3 fridgeDoorPosition;
extern glm::vec3 fridgeSize;
extern glm::vec3 counterPosition;
extern glm::vec3 counterSize;
extern glm::vec3 ovenPosition;
extern glm::vec3 ovenSize;
extern glm::vec3 burgerPosition;
extern glm::vec3 burgerSize;
extern glm::vec3 cheesePosition;
extern glm::vec3 cheeseSize;
extern glm::vec3 eggPosition;
extern glm::vec3 eggSize;
extern glm::vec3 taglierePosition;
extern glm::vec3 tagliereSize;
extern glm::vec3 insalataPosition;
extern glm::vec3 insalataSize;
extern glm::vec3 breadPosition;
extern glm::vec3 breadSize;
extern glm::vec3 hamPosition;
extern glm::vec3 hamSize;
extern glm::vec3 trashBinBodyPosition;
extern glm::vec3 trashBinBodySize;
extern glm::vec3 trashBinTopPosition;
extern glm::vec3 trashBinTopSize;
extern glm::vec3 tomatoPosition;
extern glm::vec3 tomatoSize;
extern glm::vec3 padellaPosition;
extern glm::vec3 padellaSize;
extern glm::vec3 padellaPosition2;
extern glm::vec3 ovenTopPosition;
extern glm::vec3 ovenTopSize;



extern glm::vec3 islandPositionHitbox;
extern glm::vec3 islandSizeHitbox;

extern glm::vec3 stovePositionHitbox;
extern glm::vec3 stoveSizeHitbox;

extern glm::vec3 cutboardPositionHitbox;
extern glm::vec3 cutboardSizeHitbox;

extern glm::vec3 sinkPositionHitbox;
extern glm::vec3 sinkSizeHitbox;

extern glm::vec3 ovenPositionHitbox;
extern glm::vec3 ovenSizeHitbox;

extern glm::vec3 fridgePositionHitbox;
extern glm::vec3 fridgeSizeHitbox;

extern glm::vec3 counterPositionHitbox;
extern glm::vec3 counterSizeHitbox;

extern glm::vec3 burgerPositionHitbox;
extern glm::vec3 burgerSizeHitbox;

extern glm::vec3 cheesePositionHitbox;
extern glm::vec3 cheeseSizeHitbox;

extern glm::vec3 eggPositionHitbox;
extern glm::vec3 eggSizeHitbox;

extern glm::vec3 taglierePositionHitbox;
extern glm::vec3 tagliereSizeHitbox;

extern glm::vec3 insalataPositionHitbox;
extern glm::vec3 insalataSizeHitbox;

extern glm::vec3 breadPositionHitbox;
extern glm::vec3 breadSizeHitbox;

extern glm::vec3 hamPositionHitbox;
extern glm::vec3 hamSizeHitbox;

extern glm::vec3 trashBinBodyPositionHitbox;
extern glm::vec3 trashBinBodySizeHitbox;

extern glm::vec3 trashBinTopPositionHitbox;
extern glm::vec3 trashBinTopSizeHitbox;

extern glm::vec3 tomatoPositionHitbox;
extern glm::vec3 tomatoSizeHitbox;
extern glm::vec3 padellaPositionHitbox;
extern glm::vec3 padellaSizeHitbox;


// Enum per i livelli di difficoltà
enum GameLevel {
    LEVEL_0,
    LEVEL_1,
    LEVEL_2,
	LEVEL_3,
};

// Classe per il timer del gioco
class GameTimer {
public:
    GameTimer(GameLevel level);

    void update(float deltaTime);
    void reset();
    float getTime() const;
    bool isGameOver() const;
    
    void setLevel(GameLevel newLevel);
    GameLevel getLevel();

private:
    float time;
    GameLevel level;
    bool gameOver;
    void setTimeForLevel(GameLevel level);
};


class Points {
public:
    Points();
    void resetPoints();
    int getPoints() const;
	void addPoints(int p);
	void removePoints(int p);
private: 
    int points;
};

 struct GameManager {
    GameLevel level = LEVEL_0;
    int round = 1;
    
    const int maxRounds = 3;
    const int level3TotalRounds = 5;
    
    bool isTransitioning = true;
    float transitionCountdown = 3.0f;
    Recipe currentRecipe;

    void resetTransition();
    void nextRound(Points& score);
    bool checkVictory() const;
	int sogliaPunti(GameLevel level) const;
    bool checkRoundPassed(const Points& score) const;
};


// Funzioni per la selezione delle hitbox
void checkHitboxSelections(Camera& camera, Inventory& inventory, irrklang::ISoundEngine* engine, GameTimer& timer, Points& points, Recipe& currentRecipe);

extern bool isFridgeDoorOpen;
extern float currentFridgeDoorAngle;
extern float targetFridgeDoorAngle;
extern float fridgeDoorAnimationSpeed;

extern bool isTrashcanLidOpen;
extern float currentTrashcanLidAngle;
extern float targetTrashcanLidAngle;
extern float trashcanLidAnimationSpeed;


extern GameManager gameManager;
extern GameLevel gameLevel;

// Funzione per aggiornare l'animazione della porta
void updateFridgeDoorAnimation(float deltaTime);
void updateTrashcanLidAnimation(float deltaTime);

#endif // GAME_CONTROL_H
