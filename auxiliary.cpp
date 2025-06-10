#include "auxiliary.h"

#include <map>

#include "globals.h"

extern bool fridgeInputActive;
extern std::string fridgeInputText;

static std::map<int, double> keyPressTime;
static std::map<int, bool> keyWasPressed;
const double initialRepeatDelay = 1.0;  // secondi
const double repeatInterval = 0.1;      // dopo il primo delay



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    
    if (gameState == PLAYING && !fridgeInputActive) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }


    if (fridgeInputActive) {
        for (int key = GLFW_KEY_A; key <= GLFW_KEY_Z; ++key) {
            if (shouldAcceptKey(key)) {
                fridgeInputText += static_cast<char>(key);
            }
        }

        for (int key = GLFW_KEY_0; key <= GLFW_KEY_9; ++key) {
            if (shouldAcceptKey(key)) {
                fridgeInputText += static_cast<char>(key);
            }
        }

        if (shouldAcceptKey(GLFW_KEY_SPACE)) {
            fridgeInputText += ' ';
        }

        if (shouldAcceptKey(GLFW_KEY_BACKSPACE) && !fridgeInputText.empty()) {
            fridgeInputText.pop_back();
        }


        // ESC → chiude input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            fridgeInputActive = false;
            //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }


        // ENTER → verifica input
        static bool enterPressedLastFrame = false;
        bool enterPressed = glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS;
        if (enterPressed && !enterPressedLastFrame) {
            processFridgeInput(fridgeInputText, inventory, gameManager.currentRecipe);
            fridgeInputText.clear();
            fridgeInputActive = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        enterPressedLastFrame = enterPressed;


        return;
    }

    if (gameState == PAUSE) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
    
    static bool pKeyPressedLast = false;
    bool pKeyPressed = glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS;

    if (pKeyPressed && !pKeyPressedLast) {
        if (gameState == PLAYING) {
            gameState = PAUSE;
        }
        else if (gameState == PAUSE) {
            gameState = PLAYING;
        }
    }
    pKeyPressedLast = pKeyPressed;


    if (gameState == MAIN_MENU) {
        // Handle inventory selection
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            engine->play2D("resources/media/start_key.wav");
            gameState = PLAYING;
        }
        else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            gameState = INSTRUCTIONS;
        }
        else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }

    // Handle instructions input
    if (gameState == INSTRUCTIONS) {
        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
            gameState = MAIN_MENU;
        }
    }
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

    if (gameState != PAUSE)
        camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// Function to check if a key is pressed with repeat logic
// ----------------------------------------------------------------------
bool shouldAcceptKey(int key) {
    double now = glfwGetTime();
    bool isPressed = glfwGetKey(glfwGetCurrentContext(), key) == GLFW_PRESS;

    if (!keyWasPressed[key] && isPressed) {
        keyWasPressed[key] = true;
        keyPressTime[key] = now;
        return true;
    }

    if (!isPressed) {
        keyWasPressed[key] = false;
        keyPressTime.erase(key);
        return false;
    }

    // Held down
    if (keyPressTime.count(key)) {
        double heldTime = now - keyPressTime[key];
        if (heldTime > initialRepeatDelay) {
            // repeat mode
            static std::map<int, double> lastRepeat;
            if (now - lastRepeat[key] > repeatInterval) {
                lastRepeat[key] = now;
                return true;
            }
        }
    }

    return false;
}

