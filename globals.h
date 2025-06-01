#ifndef GLOBALS_H
#define GLOBALS_H

#include "camera.h"
#include "inventory.h"
#include "text.h"
#include <irrKlang.h>

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

enum GameState {
    MAIN_MENU,
    INSTRUCTIONS,
    PLAYING,
    PAUSE,
    GAME_OVER,
    GAME_WIN
};
extern GameState gameState;

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
