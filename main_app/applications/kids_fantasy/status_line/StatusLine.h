#pragma once

#include <main_app/texture/Texture.h>
#include <main_app/font/Font.h>
#include <main_app/timer/TimerMgr.h>
#include <main_app/applications/kids_fantasy/math_logic/MathLogic.h>

enum class EStatusLineScenariosKidsFantasy
{
    eInsertCredit,
    ePressStartToRunNewGame,
    ePlayAtMaxBet,
    eWinTheMaxAmout,
    eGoodLuck,
    eWinFromLines,
    eTotalScenarioCount
};

class StatusLineKidsFantasy : public ITimer
{

private:

    /*Main alpha value key between scenarios*/
    float m_fAlphaScenario = 1.0f;

    /*Index current win element*/
    unsigned int m_unIndexWinElement = 0;

    /*Show Win Scenario*/
    bool m_bShowWinScenario = true;

    /*StatusLine current scenario*/
    EStatusLineScenariosKidsFantasy m_eCurrentScenario = EStatusLineScenariosKidsFantasy::eInsertCredit;

    /*When there is a win, this will be the current win element in different moments*/
    WinElement m_currentWinElement;

    /*Font StatusLine*/
    std::shared_ptr<Font> m_fontStatusLine;

    /*Array holding all small textures*/
    std::array<std::shared_ptr<Texture>, GameDefs::eTotalGameFiguresCount>m_arrSmallFigureTextures;

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