#include "LinesMgr.h"

#include <main_app/MainApp.h>
#include <main_app/applications/kids_fantasy/math_logic/MathLogic.h>
#include <renderer/Renderer.h>
#include <debug/Logger.h>

constexpr unsigned int g_unTimerProcessLine = 1;
constexpr unsigned int g_unTimerProcessLinePeriod = 1;

constexpr unsigned int g_unDurationProcessPointFastFirstLastSegment = 500;
constexpr unsigned int g_unDurationProcessPointFast = 280;

constexpr float g_fXBegin = -100;

bool LinesMgr::Init()
{
    m_textureParticle = Texture::CreateTexture("../src/resources/kids_fantasy/reels_area/particle_sun.png");

    if (!m_textureParticle->Load())
    {
        LOG_ERROR("LinesMgr - Unable to Load texture particle sun !");
        return false;
    }

    m_particleLine.Init(m_textureParticle, {0.0f, 0.0f});
    m_particleLine.SetVelocityVariation({0.15f, 0.07f});
    m_particleLine.SetLifeTime(200);
    m_particleLine.SetDensity(300);
    m_particleLine.SetColorStart({1.0f, 1.0f, 0.8f, 1.0f});
    m_particleLine.SetColorEnd({0.9f, 1.0f, 0.0f, 0.3f});

    m_particleHead.Init(m_textureParticle, {0.0f, 0.0f});
    m_particleHead.SetVelocityVariation({0.5f, 3.5f});
    m_particleHead.SetVelocity({-0.5f, 0.0f});
    m_particleHead.SetLifeTime(20);
    m_particleHead.SetDensity(60);
    m_particleHead.SetColorStart({1.0f, 1.0f, 0.0f, 1.0f});
    m_particleHead.SetColorEnd({0.3f, 0.3f, 0.0f, 0.0f});

    LOG_INFO("LinesMgr - Initialized ...");
    return true;
}

bool LinesMgr::Deinit()
{
    LOG_WARN("LinesMgr - Deinitialized ...");
    return true;
}

void LinesMgr::Draw()
{
    m_particleLine.Draw();
    m_particleHead.Draw();
}

void LinesMgr::OnTick(unsigned int unID, unsigned int unTimes)
{
    if (unID == g_unTimerProcessLine)
    {
        m_particleLine.SetPosition({m_fXCurrentPosition, m_fYCurrentPosition});
        m_particleHead.SetPosition({m_fXCurrentPosition, m_fYCurrentPosition});
    }
}

void LinesMgr::Start(bool bStartTimer)
{
    m_vecPositions.clear();

    /*Insert in container all win lines*/
    const auto &currentWinLine = MathLogic::GetInstance().GetWinElements().at(m_unIndexCurrentWinElement).eLine;

    for (const auto &positions : GameDefs::g_arrLines.at(currentWinLine))
    {
        m_vecPositions.emplace_back(positions);
    }

    if (bStartTimer)
    {
        MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerProcessLine, 1);
    }

    StartFirstPoint();
}

void LinesMgr::StartFirstPoint()
{
    std::function<void()> endCallback = [this]
    {
        ProcessNextPoint();
    };

    m_interpolatorX.SetEndCallback(endCallback);

    const auto &unCurrentReel = m_unIndexProcessPointAtPosition + 1;
    const auto &unCurrentPosition = m_vecPositions.at(m_unIndexProcessPointAtPosition);

    const float fXStart = g_fXBegin;
    const float fXEnd = GameDefs::g_fXReelsArea + GameDefs::g_fXOrgPosReel1 + ((GameDefs::g_fWidthFigurePictureWithFrameOffset * unCurrentReel) - (GameDefs::g_fWidthFigurePictureWithFrameOffset / 2.0f));

    const float fYStart = GameDefs::g_fYReelsArea + GameDefs::g_fYOrgPosReels + ((GameDefs::g_fHeightFigurePicture * unCurrentPosition) - (GameDefs::g_fHeightFigurePicture / 2.0f));
    const float fYEnd = fYStart;

    m_interpolatorX.Start(m_fXCurrentPosition, fXStart, fXEnd, Ease::Linear, g_unDurationProcessPointFastFirstLastSegment);
    m_interpolatorY.Start(m_fYCurrentPosition, fYStart, fYEnd, Ease::Linear, g_unDurationProcessPointFastFirstLastSegment);

    m_particleLine.StartEmitting();
    m_particleHead.StartEmitting();
}

void LinesMgr::StartEndPoint()
{
    std::function<void()> endCallback = [this]
    {
        if (++m_unIndexCurrentWinElement >= MathLogic::GetInstance().GetWinElements().size())
        {
            m_unIndexCurrentWinElement = 0;
        }

        m_unIndexProcessPointAtPosition = 0;

        Start(false);
    };

    m_interpolatorX.SetEndCallback(endCallback);

    const float fXStart = m_fXCurrentPosition;
    const float fXEnd = MainApp::GetInstance().ptrRend->SCREEN_WIDTH + std::abs(g_fXBegin);

    m_interpolatorX.Start(m_fXCurrentPosition, fXStart, fXEnd, Ease::Linear, g_unDurationProcessPointFastFirstLastSegment);
}

void LinesMgr::Stop()
{
    m_interpolatorX.Stop();
    m_interpolatorY.Stop();
    m_vecPositions.clear();
    m_unIndexProcessPointAtPosition = 0;
    m_unIndexCurrentWinElement = 0;
    m_particleLine.StopEmitting();
    m_particleHead.StopEmitting();
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unTimerProcessLine);
}

void LinesMgr::ProcessNextPoint()
{
    m_interpolatorX.Stop();
    m_interpolatorY.Stop();

    if (++m_unIndexProcessPointAtPosition >= m_vecPositions.size())
    {
        StartEndPoint();
        return;
    }

    const auto &unCurrentReel = m_unIndexProcessPointAtPosition + 1;
    const auto &unCurrentPosition = m_vecPositions.at(m_unIndexProcessPointAtPosition);

    const float fXStart = m_fXCurrentPosition;
    const float fXEnd = GameDefs::g_fXReelsArea + GameDefs::g_fXOrgPosReel1 + ((GameDefs::g_fWidthFigurePictureWithFrameOffset * unCurrentReel) - (GameDefs::g_fWidthFigurePictureWithFrameOffset / 2.0f));

    const float fYStart = m_fYCurrentPosition;
    const float fYEnd = GameDefs::g_fYReelsArea + GameDefs::g_fYOrgPosReels + ((GameDefs::g_fHeightFigurePicture * unCurrentPosition) - (GameDefs::g_fHeightFigurePicture / 2.0f));

    m_interpolatorX.Start(m_fXCurrentPosition, fXStart, fXEnd, Ease::Linear, g_unDurationProcessPointFast);
    m_interpolatorY.Start(m_fYCurrentPosition, fYStart, fYEnd, Ease::Linear, g_unDurationProcessPointFast);
}