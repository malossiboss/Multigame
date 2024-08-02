#include "StatusLine.h"

#include <main_app/applications/roulette/math_logic/RouletteMathLogic.h>
#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <main_app/panel/Panel.h>
#include <debug/Logger.h>

constexpr unsigned int g_unNormalScenarioTimer = 1;
constexpr unsigned int g_unNormalScenarioTimerPeriod = 4000;

constexpr unsigned int g_unFadeNormalScenario = 2;
constexpr unsigned int g_unFadeNormalScenarioPeriod = 1;

constexpr unsigned int g_unWinScenarioTimerFast = 3;
constexpr unsigned int g_unWinScenarioTimerFastPeriod = 1100;

constexpr unsigned int g_unWinScenarioTimerSlow = 4;
constexpr unsigned int g_unWinScenarioTimerSlowPeriod = 1100;

const std::string g_strInsertCredit = "INSERT CREDIT";
constexpr float g_fXInsetCredit = 830.0f;

const std::string g_strPlaceYourBets = "PLACE YOUR BETS";
constexpr float g_fXPlaceYourBets = 795.0f;

const std::string g_strPressStart = "PRESS START TO RUN NEW GAME";
constexpr float g_fXPressStart = 660.0f;

const std::string g_strPlayAtMaxBet = "PLAY ON MAX BET";
constexpr float g_fXPlayAtMaxBet = 795.0f;

const std::string g_strWinTheMaxAmout = "WIN THE MAX AMOUNT";
constexpr float g_fXWinTheMaxAmount = 755.0f;

const std::string g_strGoodLuck = "GOOD LUCK!";
constexpr float g_fXGoodLuck = 843.0f;

constexpr float g_fYStatusLine = 900.0f;

bool StatusLineRoulette::Init()
{
    m_fontStatusLine = Font::CreateFont("../src/fonts/Nasa.ttf", 40);

    if (!m_fontStatusLine->LoadFont())
    {
        LOG_ERROR("StatusLineRoulette - Unable to load font status line !");
        return false;
    }

    m_eCurrentScenario = EStatusLineScenariosRoulette::eInsertCredit;

    LOG_INFO("StatusLineRoulette - Initialized ...");
    return true;
}

bool StatusLineRoulette::Deinit()
{
    LOG_WARN("StatusLineRoulette - Deinitialized ...");
    return true;
}

void StatusLineRoulette::Draw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    rend->SetColor(1.0f, 1.0f, 1.0f, m_fAlphaScenario);

    switch (m_eCurrentScenario)
    {
    case EStatusLineScenariosRoulette::eInsertCredit:
    {
        rend->DrawText(g_strInsertCredit, m_fontStatusLine, g_fXInsetCredit, g_fYStatusLine);
    }
    break;

    case EStatusLineScenariosRoulette::ePlaceYourBets:
    {
        rend->DrawText(g_strPlaceYourBets, m_fontStatusLine, g_fXPlaceYourBets, g_fYStatusLine);
    }
    break;

    case EStatusLineScenariosRoulette::ePressStartToRunNewGame:
    {
        rend->DrawText(g_strPressStart, m_fontStatusLine, g_fXPressStart, g_fYStatusLine);
    }
    break;

    case EStatusLineScenariosRoulette::ePlayAtMaxBet:
    {
        rend->DrawText(g_strPlayAtMaxBet, m_fontStatusLine, g_fXPlayAtMaxBet, g_fYStatusLine);
    }
    break;

    case EStatusLineScenariosRoulette::eWinTheMaxAmout:
    {
        rend->DrawText(g_strWinTheMaxAmout, m_fontStatusLine, g_fXWinTheMaxAmount, g_fYStatusLine);
    }
    break;

    case EStatusLineScenariosRoulette::eGoodLuck:
    {
        rend->DrawText(g_strGoodLuck, m_fontStatusLine, g_fXGoodLuck, g_fYStatusLine);
    }
    break;

    case EStatusLineScenariosRoulette::eWinScenario:
    {
        if (m_bShowWinScenario)
        {
            const auto &winSector = RouletteMathLogic::GetInstance().GetCurrentWinningSector();
            /*Calculating positions*/
            std::string strColor = "RED";
            if (winSector.eColor == GameDefs::eBlack)
            {
                strColor = "BLACK";
            }
            else if(winSector.eColor == GameDefs::eZero)
            {
                strColor = "ZERO";
            }
            std::string strTextNumber = "NUMBER " + std::to_string(winSector.unWinningSectorNumber) + " " + strColor +" WINS!";
            unsigned char m_ucWidthChar = 20;
            float fTotalWidthStatusLine = strTextNumber.length() * m_ucWidthChar;
            float fXStatusLine = (rend->SCREEN_WIDTH - fTotalWidthStatusLine) / 2.0f;

            /*Draw Text Line*/
            rend->DrawText(strTextNumber, m_fontStatusLine, fXStatusLine, g_fYStatusLine);
        }
    }
    break;

    default:
        LOG_ERROR("StatusLineRoulette - Invalid StatusLine Scenario !");

        break;
    }

    rend->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void StatusLineRoulette::StartNormalScenario()
{
    m_fAlphaScenario = 1.0f;
    m_eCurrentScenario = EStatusLineScenariosRoulette::eInsertCredit;
    NextNormalScenario();
    MainApp::GetInstance().ptrTimer->StartTimer(this, g_unNormalScenarioTimer, g_unNormalScenarioTimerPeriod);
    LOG_INFO("StatusLineRoulette - Normal Scenario Started");
}

void StatusLineRoulette::StopNormalScenario()
{
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unNormalScenarioTimer);
    LOG_INFO("StatusLineRoulette - Normal Scenario Stopped");
}

void StatusLineRoulette::StartWinScenario()
{
    m_eCurrentScenario = EStatusLineScenariosRoulette::eWinScenario;
    m_fAlphaScenario = 1.0f;
    MainApp::GetInstance().ptrTimer->StartTimer(this, g_unWinScenarioTimerFast, g_unWinScenarioTimerFastPeriod);

    LOG_INFO("StatusLineRoulette - Win Scenario Started");
}

void StatusLineRoulette::StopWinScenario()
{
    m_unIndexWinElement = 0;
    m_fAlphaScenario = 1.0f;
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unWinScenarioTimerFast);
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unWinScenarioTimerSlow);
    LOG_INFO("StatusLineRoulette - Win Scenario Stopped");
}

void StatusLineRoulette::NextNormalScenario()
{
    if (!MainApp::GetInstance().ptrPanel->CanStartNewGame() &&
        !RouletteMathLogic::GetInstance().IsAnyInGameElement())
    {
        m_eCurrentScenario = EStatusLineScenariosRoulette::eInsertCredit;
        return;
    }

    switch (m_eCurrentScenario)
    {
    case EStatusLineScenariosRoulette::eInsertCredit:
    {
        m_eCurrentScenario = EStatusLineScenariosRoulette::ePlaceYourBets;
    }
    break;

    case EStatusLineScenariosRoulette::ePlaceYourBets:
    {
        m_eCurrentScenario = EStatusLineScenariosRoulette::ePressStartToRunNewGame;
    }
    break;

    case EStatusLineScenariosRoulette::ePressStartToRunNewGame:
    {
        m_eCurrentScenario = EStatusLineScenariosRoulette::ePlayAtMaxBet;
    }
    break;

    case EStatusLineScenariosRoulette::ePlayAtMaxBet:
    {
        m_eCurrentScenario = EStatusLineScenariosRoulette::eWinTheMaxAmout;
    }
    break;

    case EStatusLineScenariosRoulette::eWinTheMaxAmout:
    {
        m_eCurrentScenario = EStatusLineScenariosRoulette::ePlaceYourBets;
    }
    break;

    default:
        LOG_ERROR("StatusLineRoulette - Invalid StatusLine Scenario !");

        break;
    }
}

void StatusLineRoulette::NeedToShowGoodLuckScenario()
{
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unNormalScenarioTimer);
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unFadeNormalScenario);
    m_eCurrentScenario = EStatusLineScenariosRoulette::eGoodLuck;
    m_fAlphaScenario = 1.0f;
    m_bShowWinScenario = true;
    LOG_INFO("StatusLineRoulette - Need To Show GOOD LUCK");
}

void StatusLineRoulette::OnTick(unsigned int unID, unsigned int unTimes)
{
    if (unID == g_unNormalScenarioTimer)
    {
        /*When period reached, change scenario*/
        MainApp::GetInstance().ptrTimer->StartTimer(this, g_unFadeNormalScenario, g_unFadeNormalScenarioPeriod);
    }

    if (unID == g_unFadeNormalScenario)
    {
        const float fFadeSteps = 0.005f;
        m_fAlphaScenario -= fFadeSteps;

        if (m_fAlphaScenario <= 0.0f)
        {
            NextNormalScenario();
            MainApp::GetInstance().ptrTimer->StopTimer(this, g_unFadeNormalScenario);
            m_fAlphaScenario = 1.0f;
        }
    }

    if (unID == g_unWinScenarioTimerFast)
    {
        m_bShowWinScenario = !m_bShowWinScenario;
        if (m_bShowWinScenario)
        {
            return;
        }
    }

    if (unID == g_unWinScenarioTimerSlow)
    {
        m_bShowWinScenario = !m_bShowWinScenario;
        if (m_bShowWinScenario)
        {
            return;
        }
    }
}