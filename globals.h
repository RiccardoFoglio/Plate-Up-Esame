#ifndef GLOBALS_H
#define GLOBALS_H

#include "camera.h"
#include "inventory.h"
#include "text.h"
#include <irrKlang.h>
#include "game_control.h"
#include "bonus_malus.h"

extern BonusMalus bonusMalus;

extern const bool DEBUG;
extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;
extern float aspectRatio;
extern int selectedIndex;

extern Camera camera;
extern float lastX;
extern float lastY;
extern bool firstMouse;

extern float deltaTime;
extern float lastFrame;

extern bool isPaused;
extern bool renderTheGame;

extern bool isLoading;
extern float loadingValue; // da 0.0 a 100.0
extern float targetMin;
extern float targetMax;
extern bool showTargetZone;


enum GameState {
    MAIN_MENU,
    INSTRUCTIONS,
	RECORDS,
    PLAYING,
    PAUSE,
    GAME_OVER,
    GAME_WIN
};
extern GameState gameState;
extern GameManager gameManager; 

extern Text inventoryText;
extern Inventory inventory;

extern irrklang::ISoundEngine* engine;

extern float planeVertices[];
extern const int planeVerticesCount;

extern float wallVertices[];
extern const int wallVerticesCount;

extern float displayWallVertices[];
extern const int displayWallVerticesCount;

extern float CubeLightVertices[];
extern const int CubeLightVerticesCount;

extern float crosshairVertices[];
extern const int crosshairVerticesCount;

extern float hitboxVertices[];
extern const int hitboxVerticesCount;

extern unsigned int hitboxIndices[];
extern const int hitboxIndicesCount;

#endif // GLOBALS_H
