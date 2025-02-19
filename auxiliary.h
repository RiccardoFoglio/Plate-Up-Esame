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


// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// text
Text inventoryText(SCR_WIDTH, SCR_HEIGHT);

// inventory
Inventory inventory(true);

// sound engine
irrklang::ISoundEngine* engine;

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
     5.0f,  4.5f, -5.0f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
     5.0f,  4.5f, -5.0f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
    -5.0f,  4.5f, -5.0f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,

    // Parete anteriore
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
     5.0f, -0.5f,  5.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
     5.0f,  4.5f,  5.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
     5.0f,  4.5f,  5.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    -5.0f,  4.5f,  5.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

    // Parete sinistra
    -5.0f, -0.5f, -5.0f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
    -5.0f,  4.5f,  5.0f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    -5.0f,  4.5f,  5.0f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    -5.0f,  4.5f, -5.0f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -5.0f, -0.5f, -5.0f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

    // Parete destra
     5.0f, -0.5f, -5.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
     5.0f, -0.5f,  5.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
     5.0f,  4.5f,  5.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
     5.0f,  4.5f,  5.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
     5.0f,  4.5f, -5.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     5.0f, -0.5f, -5.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

     // Soffitto
     -5.0f,  4.5f, -5.0f,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
      5.0f,  4.5f, -5.0f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
      5.0f,  4.5f,  5.0f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
      5.0f,  4.5f,  5.0f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
     -5.0f,  4.5f,  5.0f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
     -5.0f,  4.5f, -5.0f,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f
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




// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    aspectRatio = (float)width / (float)height;
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
#endif // !AUXILIARY_H
