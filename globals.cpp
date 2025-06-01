
#include "globals.h"


const bool DEBUG = false;
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
float aspectRatio = (float)SCR_WIDTH / (float)SCR_HEIGHT;
int selectedIndex = 0;


// Camera e input
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Tempo
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Stato di gioco
bool isPaused = false;
bool renderTheGame = true;
GameState gameState = MAIN_MENU;

// UI e inventario
Text inventoryText(SCR_WIDTH, SCR_HEIGHT);
Inventory inventory(10);

// Suono
irrklang::ISoundEngine* engine = nullptr;
// Vertices for Entities



float planeVertices[] = {
    // positions          // normals           // texture Coords
     5.0f, -0.5f,  5.0f,  0.0f, 1.0f, 0.0f,  4.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 1.0f, 0.0f,  0.0f, 4.0f,

     5.0f, -0.5f,  5.0f,  0.0f, 1.0f, 0.0f,  4.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 1.0f, 0.0f,  0.0f, 4.0f,
     5.0f, -0.5f, -5.0f,  0.0f, 1.0f, 0.0f,  4.0f, 4.0f
};

const int planeVerticesCount = sizeof(planeVertices) / sizeof(float);

float wallVertices[] = {
    // Parete posteriore
    -5.0f, -0.5f, -5.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
     5.0f, -0.5f, -5.0f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
     5.0f,  3.0f, -5.0f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
     5.0f,  3.0f, -5.0f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
    -5.0f,  3.0f, -5.0f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,

    // Parete anteriore
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
     5.0f, -0.5f,  5.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
     5.0f,  3.0f,  5.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
     5.0f,  3.0f,  5.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    -5.0f,  3.0f,  5.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

    // Parete sinistra
    -5.0f, -0.5f, -5.0f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
    -5.0f,  3.0f,  5.0f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    -5.0f,  3.0f,  5.0f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    -5.0f,  3.0f, -5.0f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -5.0f, -0.5f, -5.0f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

    // Parete destra
     5.0f, -0.5f, -5.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
     5.0f, -0.5f,  5.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
     5.0f,  3.0f,  5.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
     5.0f,  3.0f,  5.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
     5.0f,  3.0f, -5.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     5.0f, -0.5f, -5.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

     // Soffitto
     -5.0f,  3.0f, -5.0f,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
      5.0f,  3.0f, -5.0f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
      5.0f,  3.0f,  5.0f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
      5.0f,  3.0f,  5.0f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
     -5.0f,  3.0f,  5.0f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
     -5.0f,  3.0f, -5.0f,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f
};

const int wallVerticesCount = sizeof(wallVertices) / sizeof(float);

float displayWallVertices[] = {

    // Poster centrato orizzontalmente, alto 1.5 unit�
  -0.5f,  1.0f, -5.0f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f,
   0.5f,  1.0f, -5.0f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
   0.5f,  2.5f, -5.0f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
   0.5f,  2.5f, -5.0f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
  -0.5f,  2.5f, -5.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
  -0.5f,  1.0f, -5.0f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f,

};


const int displayWallVerticesCount = sizeof(displayWallVertices) / sizeof(float);

float CubeLightVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

const int CubeLightVerticesCount = sizeof(CubeLightVertices) / sizeof(float);

float crosshairVertices[] = {
        -0.03f / aspectRatio,  0.0f,
         0.03f / aspectRatio,  0.0f,
          0.0f, -0.03f,
          0.0f,  0.03f
};

const int crosshairVerticesCount = sizeof(crosshairVertices) / sizeof(float);

float hitboxVertices[] = {
    // Front face
    -0.5f, -0.5f,  0.5f, // Bottom-left
     0.5f, -0.5f,  0.5f, // Bottom-right
     0.5f,  0.5f,  0.5f, // Top-right
    -0.5f,  0.5f,  0.5f, // Top-left

    // Back face
    -0.5f, -0.5f, -0.5f, // Bottom-left
     0.5f, -0.5f, -0.5f, // Bottom-right
     0.5f,  0.5f, -0.5f, // Top-right
    -0.5f,  0.5f, -0.5f  // Top-left
};

const int hitboxVerticesCount = sizeof(hitboxVertices) / sizeof(float);

unsigned int hitboxIndices[] = {
    // Front face
    0, 1, 1, 2, 2, 3, 3, 0,
    // Back face
    4, 5, 5, 6, 6, 7, 7, 4,
    // Connecting edges
    0, 4, 1, 5, 2, 6, 3, 7
}; 

const int hitboxIndicesCount = sizeof(hitboxIndices) / sizeof(unsigned int);





