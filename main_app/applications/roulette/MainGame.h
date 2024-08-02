#pragma once

#include <string>

#include <main_app/applications/IApp.h>
#include <main_app/applications/roulette/status_line/StatusLine.h>
#include <main_app/applications/roulette/table_area/TableArea.h>
#include <main_app/applications/roulette/wheel_area/WheelArea.h>
#include <main_app/texture/Texture.h>
#include <main_app/timer/TimerMgr.h>

enum class ERouletteStates
{
    eInactive,
    eReadyForGame,
    eSpinning,
    eAfterSpinningStopped,
    eWinFromGame,
    eNoWinFromGame,
    eTotalStatesCount
};

class Roulette : public IApp, public ITimer
{

private:
    std::string m_strAppName = "Roulette";

    /*Demo Menu Flag*/
    bool m_bDemoMenu = false;

    /*Roulette States*/
    ERouletteStates m_eState = ERouletteStates::eInactive;

    /*Texture main background*/
    std::shared_ptr<Texture> m_textureBackground;

    /*Wheel Area Object*/
    WheelArea m_wheelArea;

    /*Table Area Objet*/
    TableArea m_tableArea;

    /*StatusLine object*/
    StatusLineRoulette m_statusLine;

    /*Game State Request*/
    void RequestState(ERouletteStates eStateToRequest);

    /*Method called when need to start new game*/
    void StartNewGame(int unDemoSectorNumber = -1);

    /*Method called when after spinning stopped has beed invoked*/
    void AfterSpinningStopped();

    /*When game finished, reset to start new game*/
    void ResetGameElements();

    /*Draw Demo Menu*/
    void DrawDemoMenu();

public:
    Roulette();

    bool Init() override;
    bool Deinit() override;
    bool HandleEvent() override;
    const std::string &GetAppName() override;
    void OnEnter() override;
    void OnExit() override;
    void OnDraw() override;
    void OnTick(unsigned int unID, unsigned int unTimes) final;
};
