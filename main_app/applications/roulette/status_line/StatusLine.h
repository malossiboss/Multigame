#pragma once

#include <main_app/texture/Texture.h>
#include <main_app/font/Font.h>
#include <main_app/timer/TimerMgr.h>

enum class EStatusLineScenariosRoulette
{
    eInsertCredit,
    ePlaceYourBets,
    ePressStartToRunNewGame,
    ePlayAtMaxBet,
    eWinTheMaxAmout,
    eGoodLuck,
    eWinScenario,
    eTotalScenarioCount
};

class StatusLineRoulette : public ITimer
{

private:

    /*Main alpha value key between scenarios*/
    float m_fAlphaScenario = 1.0f;

    /*Index current win element*/
    unsigned int m_unIndexWinElement = 0;

    /*Show Win Scenario*/
    bool m_bShowWinScenario = true;

    /*StatusLine current scenario*/
    EStatusLineScenariosRoulette m_eCurrentScenario = EStatusLineScenariosRoulette::eInsertCredit;

    /*Font StatusLine*/
    std::shared_ptr<Font> m_fontStatusLine;

    /*Method that changed the StatusLine scenario*/
    void NextNormalScenario();

public:

    bool Init();
    bool Deinit(); 
    void Draw();
    void StartNormalScenario();
    void StopNormalScenario();
    void StartWinScenario();
    void StopWinScenario();
    void NeedToShowGoodLuckScenario();
    void OnTick(unsigned int unID, unsigned int unTimes) final;

};