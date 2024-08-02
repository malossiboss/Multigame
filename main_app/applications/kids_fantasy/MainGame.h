#pragma once

#include <string>
#include <thread>

#include <main_app/applications/IApp.h>
#include <main_app/texture/Texture.h>
#include <main_app/timer/TimerMgr.h>
#include <main_app/particle_system/ParticleSystem.h>
#include <main_app/applications/kids_fantasy/lines/LinesMgr.h>
#include <main_app/applications/kids_fantasy/reels_area/ReelsArea.h>
#include <main_app/applications/kids_fantasy/status_line/StatusLine.h>

class KidsFantasy : public IApp, public ITimer
{

private:

    enum class EKidsFantasyStates
    {
        eInactive,
        eReadyForGame,
        eReeling,
        eAfterReelingStopped,
        eWinFromGame,
        eTotalStatesCount
    };

    std::string m_strAppName = "Kids Fantasy";

    /*Flag Demo Menu*/
    bool m_bDemoMenu = false;

    /*Flag showing when loading thread finished*/
    bool m_bHasFinishedLoadingOfSurfaces = false;

    /*Flag Demo Mode Active*/
    bool m_bDemoModeActive = false;
    int m_unCounterSecondsDemoMode = 0;

    /*KidsFantasy current state*/
    EKidsFantasyStates m_eState = EKidsFantasyStates::eInactive;

    /*Reels Area object*/
    ReelsArea m_reelsArea;

    /*StatusLine object*/
    StatusLineKidsFantasy m_statusLine;

    /*LinesMgr object*/
    LinesMgr m_lines;

    /*Texture main background*/
    std::shared_ptr<Texture>m_textureBackground;

    /*Method called when start button pressed*/
    void InvokeStartButton(bool bDemoMode = false);

    /*After reeling stopped method, called when all reels stopped after game started*/
    void AfterReelingStopped();
    
    /*Game State Request*/
    void RequestState(EKidsFantasyStates eStateToRequest);

    /*Game Demo*/
    void DrawDemo();

    /*Particle test*/
    ParticleSystem m_particle;

    /*Thread Animation loading when entering in game*/
    std::thread m_threadAnimationLoading;

public:

    KidsFantasy();

    bool Init() override;
    bool Deinit() override;
    bool HandleEvent() override;
    const std::string& GetAppName() override;
    void OnEnter() override;
    void OnExit() override;
    void OnDraw() override;
    void OnTick(unsigned int unID, unsigned int unTimes) final;
};