#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/intersect.hpp> // For ray-box intersection
#include <iostream>
#include <map>
#include <string>
#include <irrKlang.h>
#include <ft2build.h>  //for text rendering

#include "camera.h"
#include "inventory.h"
#include "text.h"

#include FT_FREETYPE_H

const bool DEBUG = true;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float aspectRatio = (float)SCR_WIDTH / (float)SCR_HEIGHT; // 1.3333
int selectedIndex = 0;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

bool isPaused = false;
bool renderTheGame = false;


// Game states
enum GameState {
    MAIN_MENU,
    INSTRUCTIONS,
    PLAYING,
    PAUSE,
    GAME_OVER,
	GAME_WIN
};

GameState gameState = MAIN_MENU;


// text
Text inventoryText(SCR_WIDTH, SCR_HEIGHT);

// inventory
Inventory inventory(true);

// sound engine
irrklang::ISoundEngine* engine;

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

float displayWallVertices[] = {
    
    // Poster centrato orizzontalmente, alto 1.5 unit�
  -0.5f,  1.0f, -5.0f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f,
   0.5f,  1.0f, -5.0f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
   0.5f,  2.5f, -5.0f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
   0.5f,  2.5f, -5.0f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
  -0.5f,  2.5f, -5.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
  -0.5f,  1.0f, -5.0f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f,

};

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

float crosshairVertices[] = {
        -0.03f / aspectRatio,  0.0f,
         0.03f / aspectRatio,  0.0f,
          0.0f, -0.03f,
          0.0f,  0.03f
};

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

// Indices for rendering edges (pairs of vertices)
unsigned int hitboxIndices[] = {
    // Front face
    0, 1, 1, 2, 2, 3, 3, 0,
    // Back face
    4, 5, 5, 6, 6, 7, 7, 4,
    // Connecting edges
    0, 4, 1, 5, 2, 6, 3, 7
};


void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);





#endif // !AUXILIARY_H