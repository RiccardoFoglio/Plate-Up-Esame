#ifndef TEXT_H
#define TEXT_H

#include <map>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "shader.h"

class Text
{
public:

    unsigned int scr_width, scr_height;
    unsigned int textVAO, textVBO;

    Text(unsigned int scr_w, unsigned int scr_h);

    Shader SetUpCompileShaderText();
    FT_Library SetFreeType();
    std::string FindFont(std::string font_name);
    void LoadFontAsFace(FT_Library ft, std::string font_name);
    void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color, unsigned int VAO, unsigned int VBO);
    float GetTextWidth(const std::string& text, float scale);
    void RenderRectangle(float x, float y, float width, float height, glm::vec3 color);

private:

    FT_Face face;

    struct Character {
        unsigned int TextureID; // ID handle of the glyph texture
        glm::ivec2   Size;      // Size of glyph
        glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
        unsigned int Advance;   // Horizontal offset to advance to next glyph
    };

    std::map<GLchar, Character> Characters;

};
#endif
