#pragma once

#include <map>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <main_app/texture/Texture.h>
#include <shader/shader_m.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Character
{
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    GLuint     Advance;    // Offset to advance to next glyph
};

struct Font
{
    unsigned short usHeightFont;
    std::string m_sFontIDMemory = "";
    std::map<GLchar, Character> Characters;

    static std::shared_ptr<Font> CreateFont(std::string sFontID, unsigned short usHeight);
    bool LoadFont();
};