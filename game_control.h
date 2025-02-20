#ifndef GAME_CONTROL_H
#define GAME_CONTROL_H

#include <glm/glm.hpp>
#include <vector>
#include "camera.h"
#include "inventory.h"
#include "object_selection.h"
#include <irrKlang.h>

// Vettori per le posizioni e le dimensioni delle hitbox
extern glm::vec3 islandPosition;
extern glm::vec3 islandSize;
extern glm::vec3 fridgePosition;
extern glm::vec3 fridgeSize;
extern glm::vec3 counterPosition;
extern glm::vec3 counterSize;

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

// Enum per i livelli di difficoltà
enum DifficultyLevel {
    EASY,
    MEDIUM,
    HARD
};

// Classe per il timer del gioco
class GameTimer {
public:
    GameTimer(DifficultyLevel level);
    void update(float deltaTime);
    void reset();
    float getTime() const;
    bool isGameOver() const;
    void nextLevel();

private:
    float time;
    DifficultyLevel level;
    bool gameOver;
    void setTimeForLevel(DifficultyLevel level);
};

// Funzioni per la selezione delle hitbox
void checkHitboxSelections(Camera& camera, Inventory& inventory, irrklang::ISoundEngine* engine, GameTimer& timer);

#endif // GAME_CONTROL_H
