#include <libs/ft2build.h>
#include FT_FREETYPE_H
#include "Font.h"

#include <debug/Logger.h>

std::shared_ptr<Font> Font::CreateFont(std::string sFontID, unsigned short usHeight)
{
    std::shared_ptr<Font> ptrFontToReturn = std::make_shared<Font>();

    ptrFontToReturn->m_sFontIDMemory = sFontID;
    ptrFontToReturn->usHeightFont = usHeight;

    return ptrFontToReturn;
}

bool Font::LoadFont()
{    
    FT_Library ft_library;
    FT_Face ft_font;
    
    if(FT_Init_FreeType(&ft_library))
    {
        LOG_ERROR("Font - \"{0}\" failed to initialize FT_LIBRARY !", m_sFontIDMemory);
        return false;
    }
    
    if(FT_New_Face(ft_library, m_sFontIDMemory.c_str(), 0, &ft_font))
    {
        LOG_ERROR("Font - \"{0}\" failed to set font !", m_sFontIDMemory);
        return false;
    }
    
    FT_Set_Pixel_Sizes(ft_font, 0, usHeightFont);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    if(FT_Load_Char(ft_font, 'X', FT_LOAD_RENDER))
    {
        LOG_ERROR("Font - \"{0}\" failed to load Glyph !", m_sFontIDMemory);
    }
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
      
    for (GLubyte chars = 0; chars < 128; chars++)
    {
        if (FT_Load_Char(ft_font, chars, FT_LOAD_RENDER))
        {
            LOG_ERROR("Font - \"{0}\" failed to load Char !", m_sFontIDMemory);
            continue;
        }
        
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D
        (
            GL_TEXTURE_2D,
            0,
            GL_RED,
            ft_font->glyph->bitmap.width,
            ft_font->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            ft_font->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character =
        {
            texture,
            glm::ivec2(ft_font->glyph->bitmap.width, ft_font->glyph->bitmap.rows),
            glm::ivec2(ft_font->glyph->bitmap_left, ft_font->glyph->bitmap_top),
            static_cast<GLuint>(ft_font->glyph->advance.x)
        };
        
        Characters.insert(std::pair<GLchar, Character>(chars, character));
    }
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    FT_Done_Face(ft_font);
    FT_Done_FreeType(ft_library);

    LOG_INFO("Font - Loaded \"{0}\"", m_sFontIDMemory);

    return true;
}