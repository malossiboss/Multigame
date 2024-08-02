#include "MainGame.h"

#include <iostream>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <main_app/panel/Panel.h>
#include <main_app/applications/roulette/math_logic/RouletteMathLogic.h>
#include <debug/Logger.h>

ParticleBuilder::ParticleBuilder()
{
}

bool ParticleBuilder::Init()
{
    /*Reserve 10 textures*/
    m_vecTexturesParticle.reserve(10);

    /*Load Textures and insert into container*/
    auto textureSun = Texture::CreateTexture("../src/resources/particle_builder/particles/particle_sun.png");
    auto textureStar = Texture::CreateTexture("../src/resources/particle_builder/particles/particle_star.png");
    auto textureFlower = Texture::CreateTexture("../src/resources/particle_builder/particles/flower_particle.png");
    auto textureSmoke = Texture::CreateTexture("../src/resources/particle_builder/particles/smoke_particle.png");
    auto textureBubble = Texture::CreateTexture("../src/resources/particle_builder/particles/particle_bubble.png");
    auto textureDust = Texture::CreateTexture("../src/resources/particle_builder/particles/particle_dust.png");
    auto textureFire = Texture::CreateTexture("../src/resources/particle_builder/particles/particle_fire.png");
    auto textureMultistar = Texture::CreateTexture("../src/resources/particle_builder/particles/particle_multistar.png");
    auto textureFire1 = Texture::CreateTexture("../src/resources/particle_builder/particles/particle_fire_1.png");
    auto textureSmoke1 = Texture::CreateTexture("../src/resources/particle_builder/particles/particle_smoke_1.png");

    m_vecTexturesParticle.emplace_back(textureSun);
    m_vecTexturesParticle.emplace_back(textureStar);
    m_vecTexturesParticle.emplace_back(textureFlower);
    m_vecTexturesParticle.emplace_back(textureSmoke);
    m_vecTexturesParticle.emplace_back(textureBubble);
    m_vecTexturesParticle.emplace_back(textureDust);
    m_vecTexturesParticle.emplace_back(textureFire);
    m_vecTexturesParticle.emplace_back(textureMultistar);
    m_vecTexturesParticle.emplace_back(textureFire1);
    m_vecTexturesParticle.emplace_back(textureSmoke1);

    for (auto &texture : m_vecTexturesParticle)
    {
        if (!texture->Load())
        {
            LOG_ERROR("Particle Builder - Unable to load texture \"{0}\" !", texture->GetPath());
            return false;
        }
    }

    LOG_INFO("Particle Builder - Initialized ...");
    return true;
}

bool ParticleBuilder::Deinit()
{
    LOG_INFO("Roulette - Deinitalized ...");
    return true;
}

bool ParticleBuilder::HandleEvent()
{
    const auto &nXMouse = ImGui::GetMousePos().x;
    const auto &nYMouse = ImGui::GetMousePos().y;

    /*Panel Handle Event*/
    if (MainApp::GetInstance().ptrPanel->HandleEvent())
    {
        return true;
    }

    /*If calculator or volume scene active, no handle event for MainGame*/
    if (MainApp::GetInstance().ptrPanel->GetPanelInfoScene() != EPanelInfoScenes::eNoInfoScene)
    {
        return false;
    }

    /*ENTER button*/
    if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter), false))
    {
        LOG_INFO("Roulette - ENTER Button Pressed");
        return true;
    }

    return false;
}

const std::string &ParticleBuilder::GetAppName()
{
    return m_strAppName;
}

void ParticleBuilder::OnEnter()
{
    MainApp::GetInstance().ptrPanel->HideFields();
    LOG_INFO("Particle_Builder - Transition to Application succeed");
}

void ParticleBuilder::OnExit()
{
    MainApp::GetInstance().ptrPanel->ShowFields();
    LOG_INFO("Particle_Builder - Exit from Application");
}

void ParticleBuilder::DrawMainMenu()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    /*Actual Menu*/
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            /*Create New*/
            if (ImGui::BeginMenu("Create New ..."))
            {
                if (ImGui::MenuItem("Particle"))
                {
                    m_bCreateNewParticle = true;
                }

                ImGui::EndMenu();
            }

            /*Delete Existing*/
            if (ImGui::BeginMenu("Delete Existing ..."))
            {
                if (ImGui::BeginMenu("Particle"))
                {
                    for (auto &particle : m_mapParticles)
                    {
                        if (ImGui::MenuItem(particle.first.c_str()))
                        {
                            m_bDeleteExistingParticle = true;
                            m_strIDParticleToBeDeleted = particle.first;
                        }
                    }

                    ImGui::EndMenu();
                }

                ImGui::EndMenu();
            }

            ImGui::Separator();
            ImGui::MenuItem("Exit");

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    /*Popup create new particle*/
    if (m_bCreateNewParticle)
    {
        ImGui::OpenPopup("Create New Particle");
    }

    if (ImGui::BeginPopupModal("Create New Particle", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        static unsigned int unCounterDefaultName = 0;
        std::string strName = "Particle_" + std::to_string(unCounterDefaultName);

        /*Text Buff*/
        static char arrText[64] = "Particle_";
        ImGui::Text("Name:");
        ImGui::InputText(std::to_string(unCounterDefaultName).c_str(), arrText, m_unTextBuff);

        ImGui::Separator();

        ImGui::Text("Textures:");
        ImGui::Separator();

        /*Draw Textures*/
        const unsigned int unTexturesPerRow = 3;
        unsigned int unCounterRow = 0;
        for (auto texture : m_vecTexturesParticle)
        {
            const float fWSize = 75;
            const float fHSize = 75;
            ImTextureID imguiTexture = (void *)(size_t)texture->GetTextureID();
            bool bButtonPressed = ImGui::ImageButton(imguiTexture, ImVec2(fWSize, fHSize));

            /*If pressed, insert object into container*/
            if (bButtonPressed)
            {
                strName = arrText;
                if (strName.empty() || strName == "Particle_")
                {
                    strName = "Particle_" + std::to_string(unCounterDefaultName);
                }

                ParticleSystem particleObject;
                particleObject.Init(texture, {rend->SCREEN_WIDTH / 2, rend->SCREEN_HEIGHT / 2});

                m_mapParticles.insert(std::make_pair(strName, particleObject));
                auto itLast = --m_mapParticles.end();
                itLast->second.StartEmitting();

                ++unCounterDefaultName;
                m_bCreateNewParticle = false;
                ImGui::CloseCurrentPopup();
            }
            ++unCounterRow;

            if (unCounterRow < unTexturesPerRow)
            {
                ImGui::SameLine();
            }
            else
            {
                unCounterRow = 0;
            }
        }

        ImGui::Separator();

        if (ImGui::Button("Cancel", ImVec2(265, 0)))
        {
            m_bCreateNewParticle = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    /*Popup delete existing particle*/
    if (m_bDeleteExistingParticle)
    {
        ImGui::OpenPopup("Delete Existing Particle");
    }

    if (ImGui::BeginPopupModal("Delete Existing Particle", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {

        ImGui::Text("Are you sure to delete %s ?", m_strIDParticleToBeDeleted.c_str());
        ImGui::Separator();

        if (ImGui::Button("OK", ImVec2(120, 0)))
        {
            auto itDelete = m_mapParticles.find(m_strIDParticleToBeDeleted);
            if (itDelete != m_mapParticles.end())
            {
                itDelete->second.DieImmediately();
                m_mapParticles.erase(itDelete);
            }

            m_strIDParticleToBeDeleted.clear();
            m_bDeleteExistingParticle = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(120, 0)))
        {
            m_bDeleteExistingParticle = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void ParticleBuilder::DrawActiveListParticles()
{
    /*Traverse all objects to draw collapsing header*/
    for (auto &particle : m_mapParticles)
    {
        auto &particleID = particle.first;
        auto &particleObject = particle.second;

        /*Collapsing Header*/
        if (ImGui::CollapsingHeader(particleID.c_str()))
        {
            /*Drag with Mouse, Set Position*/
            ImGui::Separator();
            ImGui::TextColored({1.0f, 1.0f, 1.0f, 0.3f}, "Position:");
            static bool bDragWithMouse = false;
            bool bOrientToMotion = particleObject.GetOrientToMotion();
            ImGui::Checkbox("Drag with Mouse", &bDragWithMouse);
            ImGui::SameLine();
            ImGui::Checkbox("Orient to Motion", &bOrientToMotion);

            if (bDragWithMouse)
            {
                if (ImGui::IsMouseDragging(0))
                {
                    const float &fX = ImGui::GetMousePos().x;
                    const float &fY = ImGui::GetMousePos().y;
                    particleObject.SetPosition({fX, fY});
                }
            }

            particleObject.SetOrientToMotion(bOrientToMotion);

            /*Velocity*/
            ImGui::Separator();
            ImGui::TextColored({1.0f, 1.0f, 1.0f, 0.3f}, "Velocity Variation:");

            float fXVelocityVariation = particleObject.GetVelocityVariation().x;
            float fYVelocityVariation = particleObject.GetVelocityVariation().y;
            ImGui::DragFloat("X Velocity Variation", &fXVelocityVariation, 0.001f, 0.001f, 20.0f);
            ImGui::DragFloat("Y Velocity Variation", &fYVelocityVariation, 0.001f, 0.001f, 20.0f);
            if (ImGui::Button("Reset Variation"))
            {
                fXVelocityVariation = 1.0f;
                fYVelocityVariation = 1.0f;
            }

            particleObject.SetVelocityVariation({fXVelocityVariation, fYVelocityVariation});

            /*Velocity Variation (Wind)*/
            ImGui::Separator();
            ImGui::TextColored({1.0f, 1.0f, 1.0f, 0.3f}, "Velocity (Wind):");

            ImGui::Button("Wind Force \n(Drag to Orient) \n(Click to Reset)", ImVec2(340.0f, 340.0f));
            if (ImGui::IsItemActive())
            {
                ImGuiIO &io = ImGui::GetIO();

                /*Draw a line between the button and the mouse cursor*/
                ImDrawList *draw_list = ImGui::GetWindowDrawList();
                draw_list->PushClipRectFullScreen();
                draw_list->AddLine(io.MouseClickedPos[0], io.MousePos, ImGui::GetColorU32(ImGuiCol_PlotHistogram), 4.0f);
                draw_list->PopClipRect();

                ImVec2 value_raw = ImGui::GetMouseDragDelta(0, 0.0f);
                value_raw.x = value_raw.x / 100.0f;
                value_raw.y = value_raw.y / 100.0f;

                ImGui::SameLine();
                ImGui::Text("Force (%.1f, %.1f)", value_raw.x, value_raw.y);

                particleObject.SetVelocity({value_raw.x, value_raw.y});
            }
            ImGui::Text("X: %.1f", particleObject.GetVelocity().x);
            ImGui::SameLine();
            ImGui::Text("Y: %.1f", particleObject.GetVelocity().y);

            /*Gravity*/
            ImGui::Separator();
            ImGui::TextColored({1.0f, 1.0f, 1.0f, 0.3f}, "Gravity:");

            float fGravity = particleObject.GetGravity();
            ImGui::DragFloat("Gravity", &fGravity, 0.01f, -100.0f, 100.0f);

            if (ImGui::Button("Reset Gravity"))
            {
                fGravity = 0.0f;
            }

            particleObject.SetGravity(fGravity);

            /*Color Start*/
            ImGui::Separator();
            ImGui::TextColored({1.0f, 1.0f, 1.0f, 0.3f}, "Color Start:");

            ImVec4 vec4ColorStart = ImColor(particleObject.GetColorStart().r,
                                            particleObject.GetColorStart().g,
                                            particleObject.GetColorStart().b,
                                            particleObject.GetColorStart().a);
            ImGui::ColorEdit4("Color Start",
                              (float *)&vec4ColorStart,
                              ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_AlphaBar);

            particleObject.SetColorStart({vec4ColorStart.x, vec4ColorStart.y, vec4ColorStart.z, vec4ColorStart.w});

            /*Color End*/
            ImGui::Separator();
            ImGui::TextColored({1.0f, 1.0f, 1.0f, 0.3f}, "Color End:");

            ImVec4 vec4ColorEnd = ImColor(particleObject.GetColorEnd().r,
                                          particleObject.GetColorEnd().g,
                                          particleObject.GetColorEnd().b,
                                          particleObject.GetColorEnd().a);
            ImGui::ColorEdit4("Color End",
                              (float *)&vec4ColorEnd,
                              ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_AlphaBar);

            particleObject.SetColorEnd({vec4ColorEnd.x, vec4ColorEnd.y, vec4ColorEnd.z, vec4ColorEnd.w});

            /*Rotation*/
            ImGui::Separator();
            ImGui::TextColored({1.0f, 1.0f, 1.0f, 0.3f}, "Rotation:");

            float fRotationBegin = particleObject.GetRotationBegin();
            float fRotationEnd = particleObject.GetRotationEnd();

            ImGui::DragFloat("Rotation Begin", &fRotationBegin, 0.1f, -360.0f, 360.0f);
            if (bOrientToMotion && ImGui::IsItemHovered())
            {
                ImGui::SetTooltip("Orient to Motion Active !");
            }

            ImGui::DragFloat("Rotation End", &fRotationEnd, 0.1f, -360.0f, 360.0f);
            if (bOrientToMotion && ImGui::IsItemHovered())
            {
                ImGui::SetTooltip("Orient to Motion Active !");
            }

            if (ImGui::Button("Reset Rotation"))
            {
                fRotationBegin = 0.0f;
                fRotationEnd = 0.0f;
            }

            particleObject.SetRotationBegin(fRotationBegin);
            particleObject.SetRotationEnd(fRotationEnd);

            /*Size*/
            ImGui::Separator();
            ImGui::TextColored({1.0f, 1.0f, 1.0f, 0.3f}, "Size:");

            float fSizeBegin = particleObject.GetSizeBegin();
            float fSizeEnd = particleObject.GetSizeEnd();

            ImGui::DragFloat("Size Begin", &fSizeBegin, 0.001f, 0.001f, 10.0f);
            ImGui::DragFloat("Size End", &fSizeEnd, 0.001f, 0.001f, 10.0f);

            if (ImGui::Button("Reset Size"))
            {
                fSizeBegin = 1.0f;
                fSizeEnd = 1.0f;
            }

            particleObject.SetSizeBegin(fSizeBegin);
            particleObject.SetSizeEnd(fSizeEnd);

            /*Lifetime in cycles*/
            ImGui::Separator();
            ImGui::TextColored({1.0f, 1.0f, 1.0f, 0.3f}, "Lifetime (cycles):");

            float fLifetime = particleObject.GetLifeTime();
            ImGui::DragFloat("Lifetime", &fLifetime, 1.0f, 1.00f, 1000.0f);

            if (ImGui::Button("Reset Lifetime"))
            {
                fLifetime = 100.0f;
            }

            particleObject.SetLifeTime(fLifetime);

            /*Density*/
            ImGui::Separator();
            ImGui::TextColored({1.0f, 1.0f, 1.0f, 0.3f}, "Density (amount particles):");

            float fDensity = particleObject.GetDensity();
            ImGui::DragFloat("Density", &fDensity, 1.0f, 1.00f, 1000.0f);

            if (ImGui::Button("Reset Density"))
            {
                fDensity = 200.0f;
            }

            particleObject.SetDensity(fDensity);
        }
    }
}

void ParticleBuilder::OnDraw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    /*Draw Particles*/
    for (auto &particle : m_mapParticles)
    {
        particle.second.Draw();
    }

    /*Main menu window flags*/
    ImGuiWindowFlags mainMenuFlags = 0;
    mainMenuFlags |= ImGuiWindowFlags_NoMove;
    mainMenuFlags |= ImGuiWindowFlags_NoResize;
    mainMenuFlags |= ImGuiWindowFlags_MenuBar;

    /*Set position and size*/
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(520, 920), ImGuiCond_FirstUseEver);

    /*Actual window*/
    ImGui::Begin("Particle Builder", &m_bMainMenuFlag, mainMenuFlags);

    /*Draw Main Menu*/
    DrawMainMenu();

    /*Draw List Particles*/
    DrawActiveListParticles();

    /*End Actual Window*/
    ImGui::End();

    /*Draw Panel*/
    MainApp::GetInstance().ptrPanel->OnDraw();
}

void ParticleBuilder::OnTick(unsigned int unID, unsigned int unTimes)
{
}