#include "ReelsArea.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <main_app/audio_player/AudioPlayer.h>
#include <main_app/panel/Panel.h>
#include <main_app/applications/kids_fantasy/math_logic/MathLogic.h>
#include <debug/Logger.h>

constexpr unsigned int g_unReelingListenerTimer = 1;
constexpr float g_fFpsReelAnimations = 20.0f;
constexpr float g_fXHearth = 673.0;

bool ReelsArea::Init()
{

    /*Load textures*/
    m_textureReelsArea = Texture::CreateTexture("../src/resources/kids_fantasy/reels_area/reels_area_clean.png");
    m_textureHearth = Texture::CreateTexture("../src/resources/kids_fantasy/reels_area/hearth.png");

    if (!m_textureReelsArea->Load())
    {
        LOG_ERROR("Reels Area - Unable to load texture reels area !");
        return false;
    }

    if (!m_textureHearth->Load())
    {
        LOG_ERROR("Reels Area - Unable to load texture hearth !");
        return false;
    }

    /*Figures Texutres*/
    m_arrFiguresTexture.at(GameDefs::eGameFigureOne) = Texture::CreateTexture("../src/resources/kids_fantasy/reels_area/reel_figures/figure_1.png");
    m_arrFiguresTexture.at(GameDefs::eGameFigureTwo) = Texture::CreateTexture("../src/resources/kids_fantasy/reels_area/reel_figures/figure_2.png");
    m_arrFiguresTexture.at(GameDefs::eGameFigureThree) = Texture::CreateTexture("../src/resources/kids_fantasy/reels_area/reel_figures/figure_3.png");
    m_arrFiguresTexture.at(GameDefs::eGameFigureFour) = Texture::CreateTexture("../src/resources/kids_fantasy/reels_area/reel_figures/figure_4.png");
    m_arrFiguresTexture.at(GameDefs::eGameFigureFive) = Texture::CreateTexture("../src/resources/kids_fantasy/reels_area/reel_figures/figure_5.png");
    m_arrFiguresTexture.at(GameDefs::eGameFigureSix) = Texture::CreateTexture("../src/resources/kids_fantasy/reels_area/reel_figures/figure_6.png");

    for (auto &texture : m_arrFiguresTexture)
    {
        if (!texture->Load())
        {
            LOG_ERROR("Reels Area - Unable to load texture figure \"{0}\"", texture->GetPath());
            return false;
        }
    }

    /*Initialize Reels*/
    if (!m_arrReels.at(GameDefs::eFirstReel).Init(GameDefs::eFirstReel, GameDefs::g_fXReelsArea + GameDefs::g_fXOrgPosReel1, GameDefs::g_fYReelsArea + GameDefs::g_fYOrgPosReels, m_arrFiguresTexture))
    {
        LOG_ERROR("Reels Area - Unable to load reel 1!");
        return false;
    }
    if (!m_arrReels.at(GameDefs::eSecondReel).Init(GameDefs::eSecondReel, GameDefs::g_fXReelsArea + GameDefs::g_fXOrgPosReel2, GameDefs::g_fYReelsArea + GameDefs::g_fYOrgPosReels, m_arrFiguresTexture))
    {
        LOG_ERROR("Reels Area - Unable to load reel 2!");
        return false;
    }
    if (!m_arrReels.at(GameDefs::eThirdReel).Init(GameDefs::eThirdReel, GameDefs::g_fXReelsArea + GameDefs::g_fXOrgPosReel3, GameDefs::g_fYReelsArea + GameDefs::g_fYOrgPosReels, m_arrFiguresTexture))
    {
        LOG_ERROR("Reels Area - Unable to load reel 3 !");
        return false;
    }
    if (!m_arrReels.at(GameDefs::eFourthReel).Init(GameDefs::eFourthReel, GameDefs::g_fXReelsArea + GameDefs::g_fXOrgPosReel4, GameDefs::g_fYReelsArea + GameDefs::g_fYOrgPosReels, m_arrFiguresTexture))
    {
        LOG_ERROR("Reels Area - Unable to load reel 4 !");
        return false;
    }
    if (!m_arrReels.at(GameDefs::eFifthReel).Init(GameDefs::eFifthReel, GameDefs::g_fXReelsArea + GameDefs::g_fXOrgPosReel5, GameDefs::g_fYReelsArea + GameDefs::g_fYOrgPosReels, m_arrFiguresTexture))
    {
        LOG_ERROR("Reels Area - Unable to load reel 5!");
        return false;
    }

    LOG_INFO("Reels Area - Initialized ...");
    return true;
}

bool ReelsArea::Deinit()
{
    UnloadResources();

    LOG_WARN("Reels Area - Deinitialized ...");
    return true;
}

bool ReelsArea::HandleEvent()
{
    const auto &nXMouse = ImGui::GetMousePos().x;
    const auto &nYMouse = ImGui::GetMousePos().y;

    return false;
}

bool ReelsArea::StartNewGame(bool bDemoMode)
{
    /*Check if all reels stopped*/
    bool bCanStartReeling = true;
    for (auto &reel : m_arrReels)
    {
        if (reel.GetReelState() != EReelState::eStopped)
        {
            bCanStartReeling = false;
            return bCanStartReeling;
        }
    }

    if (bCanStartReeling)
    {
        /*Check if credit sufficient*/
        if (!MainApp::GetInstance().ptrPanel->CanStartNewGame())
        {
            LOG_ERROR("ReelsArea - Cannot Start New Game! Insufficient credit !");
            bCanStartReeling = false;
            return bCanStartReeling;
        }

        /*Decrement bet from total credit*/
        MainApp::GetInstance().ptrPanel->DecrementCreditWithBet();

        /*Generate New Results*/
        if (!bDemoMode)
        {
            MathLogic::GetInstance().GenerateResults();
        }

        for (auto &reel : m_arrReels)
        {
            reel.StartReeling();
        }

        /*Start listener timer to check if all reels stopped*/
        MainApp::GetInstance().ptrTimer->StartTimer(this, g_unReelingListenerTimer, 1);
    }

    LOG_INFO("Reels Area - New Game Started");
    return bCanStartReeling;
}

void ReelsArea::SetAfterReelingStoppedCallback(std::function<void()> &afterReelingStoppedCallback)
{
    m_afterReelingStoppedCallback = afterReelingStoppedCallback;
}

void ReelsArea::Draw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    /*Draw Reels Area*/
    rend->DrawPicture(m_textureReelsArea, GameDefs::g_fXReelsArea, GameDefs::g_fYReelsArea);

    /*Draw Reels*/
    for (auto &reel : m_arrReels)
    {
        reel.Draw();
    }

    /*Draw hearth*/
    rend->DrawPicture(m_textureHearth, GameDefs::g_fXReelsArea + g_fXHearth, GameDefs::g_fYReelsArea);
}

void ReelsArea::OnTick(unsigned int unID, unsigned int unTimes)
{
    if (unID == g_unReelingListenerTimer)
    {
        bool bReelsStopped = true;
        for (auto &reel : m_arrReels)
        {
            if (reel.GetReelState() != EReelState::eStopped)
            {
                bReelsStopped = false;
                return;
            }
        }

        if (bReelsStopped)
        {
            /*After all reels stopped, call the callback*/
            MainApp::GetInstance().ptrTimer->StopTimer(this, g_unReelingListenerTimer);
            if (m_afterReelingStoppedCallback)
            {
                m_afterReelingStoppedCallback();
                StartAnimationsIfAny();
            }
        }
    }
}

void ReelsArea::StartAnimationsIfAny()
{
    const auto &containerWins = MathLogic::GetInstance().GetWinElements();
    if (containerWins.empty())
    {
        return;
    }

    bool bSoundStarted = false;
    for (const auto &win : containerWins)
    {
        for (unsigned int i = 0; i < win.unFigureCount; ++i)
        {
            const auto &unFigurePositionToStartAnim = GameDefs::g_arrLines.at(win.eLine).at(i);
            m_arrReels.at(i).StartAnimation(unFigurePositionToStartAnim, win.eGameFigure);

            /*If first figure, play sound*/
            if(!bSoundStarted && i == 0)
            {
                std::string strFigureSound = "../src/resources/kids_fantasy/sounds/fig_" + std::to_string(win.eGameFigure + 1) + "_sound.wav";
                MainApp::GetInstance().ptrAudioPlayer->PlaySound(strFigureSound);
                bSoundStarted = true;
            }
        }
    }
}

void ReelsArea::LoadAnimationSurfaces()
{
    /*Figures Animations*/
    m_arrFiguresAnimations.at(GameDefs::eGameFigureOne).InitSurfaces("../src/resources/kids_fantasy/reels_area/reel_animations/figure_1", g_fFpsReelAnimations);
    m_arrFiguresAnimations.at(GameDefs::eGameFigureTwo).InitSurfaces("../src/resources/kids_fantasy/reels_area/reel_animations/figure_2", g_fFpsReelAnimations);
    m_arrFiguresAnimations.at(GameDefs::eGameFigureThree).InitSurfaces("../src/resources/kids_fantasy/reels_area/reel_animations/figure_3", g_fFpsReelAnimations);
    m_arrFiguresAnimations.at(GameDefs::eGameFigureFour).InitSurfaces("../src/resources/kids_fantasy/reels_area/reel_animations/figure_4", g_fFpsReelAnimations);
    m_arrFiguresAnimations.at(GameDefs::eGameFigureFive).InitSurfaces("../src/resources/kids_fantasy/reels_area/reel_animations/figure_5", g_fFpsReelAnimations);
    m_arrFiguresAnimations.at(GameDefs::eGameFigureSix).InitSurfaces("../src/resources/kids_fantasy/reels_area/reel_animations/figure_6", g_fFpsReelAnimations);
}

void ReelsArea::LoadTexturesFromSurfaces()
{
    m_arrFiguresAnimations.at(GameDefs::eGameFigureOne).LoadTexturesFromSurfaces();
    m_arrFiguresAnimations.at(GameDefs::eGameFigureTwo).LoadTexturesFromSurfaces();
    m_arrFiguresAnimations.at(GameDefs::eGameFigureThree).LoadTexturesFromSurfaces();
    m_arrFiguresAnimations.at(GameDefs::eGameFigureFour).LoadTexturesFromSurfaces();
    m_arrFiguresAnimations.at(GameDefs::eGameFigureFive).LoadTexturesFromSurfaces();
    m_arrFiguresAnimations.at(GameDefs::eGameFigureSix).LoadTexturesFromSurfaces();

    if (!m_arrReels.at(GameDefs::eFirstReel).InitFiguresAnimations(m_arrFiguresAnimations))
    {
        LOG_ERROR("Reels Area - Unable to InitFiguresAnimations reel 1!");
        return;
    }

    if (!m_arrReels.at(GameDefs::eSecondReel).InitFiguresAnimations(m_arrFiguresAnimations))
    {
        LOG_ERROR("Reels Area - Unable to InitFiguresAnimations reel 2!");
        return;
    }

    if (!m_arrReels.at(GameDefs::eThirdReel).InitFiguresAnimations(m_arrFiguresAnimations))
    {
        LOG_ERROR("Reels Area - Unable to InitFiguresAnimations reel 3!");
        return;
    }

    if (!m_arrReels.at(GameDefs::eFourthReel).InitFiguresAnimations(m_arrFiguresAnimations))
    {
        LOG_ERROR("Reels Area - Unable to InitFiguresAnimations reel 4!");
        return;
    }

    if (!m_arrReels.at(GameDefs::eFifthReel).InitFiguresAnimations(m_arrFiguresAnimations))
    {
        LOG_ERROR("Reels Area - Unable to InitFiguresAnimations reel 5!");
        return;
    }
}

void ReelsArea::UnloadResources()
{
    m_arrFiguresAnimations.at(GameDefs::eGameFigureOne).Deinit();
    m_arrFiguresAnimations.at(GameDefs::eGameFigureTwo).Deinit();
    m_arrFiguresAnimations.at(GameDefs::eGameFigureThree).Deinit();
    m_arrFiguresAnimations.at(GameDefs::eGameFigureFour).Deinit();
    m_arrFiguresAnimations.at(GameDefs::eGameFigureFive).Deinit();
    m_arrFiguresAnimations.at(GameDefs::eGameFigureSix).Deinit();
}