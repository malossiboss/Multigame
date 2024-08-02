#pragma once

#include <string>
#include <main_app/texture/Texture.h>
#include <main_app/font/Font.h>

    struct Button
    {
        float fX = 0.0f;
        float fY = 0.0f;
        float fValue = 0.0f;
        bool bIsClicked = false;
        bool bIsHovered = false;
        bool bIsLocked = false;
        std::string strText = "";
        std::shared_ptr<Texture>textureButton = nullptr;
        std::shared_ptr<Font>fontButton = nullptr;
        glm::vec4 colorButton = {1.0f, 1.0f, 1.0f, 1.0f};
        bool IsHovered(const int& nXMouse, const int& nYMouse);
        bool IsPressed(const int& nXMouse, const int& nYMouse);
        bool IsPressAndHold(const int& nXMouse, const int& nYMouse);
        bool IsReleased(const int& nXMouse, const int& nYMouse);
    };