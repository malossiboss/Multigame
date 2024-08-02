#include "Button.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <debug/Logger.h>

bool Button::IsHovered(const int& nXMouse, const int& nYMouse)
{
    if(nXMouse >= fX && nXMouse <= (fX + textureButton->GetWidth()) && 
       nYMouse >= fY && nYMouse <= (fY + textureButton->GetHeight()))
    {
        bIsHovered = true;
        return true;
    }

    bIsHovered = false;
    return false;
}

bool Button::IsPressed(const int& nXMouse, const int& nYMouse)
{
    if(IsHovered(nXMouse, nYMouse) && ImGui::IsMouseClicked(0))
    {
        bIsClicked = true;
        return true;
    }

    return false;
}

bool Button::IsPressAndHold(const int& nXMouse, const int& nYMouse)
{
    if(IsHovered(nXMouse, nYMouse) && ImGui::IsMouseDown(0))
    {
        bIsClicked = true;
        return true;
    }

    return false;
}

bool Button::IsReleased(const int& nXMouse, const int& nYMouse)
{
    if(bIsClicked && ImGui::IsMouseReleased(0))
    {
        bIsClicked = false;
        bIsHovered = false;
        return true;
    }

    return false;
}