#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/intersect.hpp>
#include <iostream>
#include <map>
#include <string>
#include <irrKlang.h>
#include <ft2build.h>  

#include "globals.h"    
#include "camera.h"
#include "inventory.h"
#include "text.h"

#include FT_FREETYPE_H

// Callback e input
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
bool shouldAcceptKey(int key);

#endif // AUXILIARY_H
