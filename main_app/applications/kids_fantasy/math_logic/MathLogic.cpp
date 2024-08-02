#include "MathLogic.h"

#include <cstdlib>
#include <iostream>
#include <main_app/panel/Panel.h>
#include <debug/Logger.h>

MathLogic::MathLogic()
{
}

MathLogic::~MathLogic()
{
}

bool MathLogic::Init()
{

    LOG_INFO("MathLogic - KidsFantasy - Initialized ...");
    return true;
}

bool MathLogic::Deinit()
{
    LOG_WARN("MathLogic - KidsFantasy - Deinitialized ...");
    return true;
}

bool MathLogic::ThereIsAWin()
{
    return !m_vectorWins.empty();
}

long MathLogic::GenerateRandomNuber(long nLowerBound, long nUpperBound)
{
    unsigned int unSeed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(unSeed);
    long nNumberToReturn = rand() % nUpperBound + nLowerBound;

    // LOG_INFO("MathLogic - KidsFantasy - Generated Random Number - \"{0}\"", nNumberToReturn);

    return nNumberToReturn;
}

void MathLogic::GenerateResults()
{
    /*Clear container with wins*/
    m_vectorWins.clear();

    /*Generate random numbers with rand()*/
    for (unsigned int figure = GameDefs::eFirstPositionNONVisible; figure < GameDefs::eTotalFigurePositionsPerReel; ++figure)
    {
        for (unsigned int reel = GameDefs::eFirstReel; reel < GameDefs::eTotalReelCount; ++reel)
        {
            m_arrResults[figure][reel] = (GameDefs::EGameFigure)GenerateRandomNuber(GameDefs::eGameFigureOne, GameDefs::eTotalGameFiguresCount);
        }
    }

    /*Here is just a print logic*/
    LOG_WARN("MathLogic - KidsFantasy - Generated Results BEGIN ");
    for (unsigned int figure = GameDefs::eFirstPositionNONVisible; figure < GameDefs::eTotalFigurePositionsPerReel; ++figure)
    {
        for (unsigned int reel = GameDefs::eFirstReel; reel < GameDefs::eTotalReelCount; ++reel)
        {
            std::cout << m_arrResults[figure][reel] + 1 << "   ";
        }

        std::cout << std::endl;
    }
    LOG_WARN("MathLogic - KidsFantasy - Generated Results END ");

    /*Check for Lines win*/
    CheckForWins();

    /*Here is just a print logic of the lines*/
    if (!m_vectorWins.empty())
    {
        LOG_WARN("MathLogic - KidsFantasy - Win Element BEGIN ");
        for (const auto &element : m_vectorWins)
        {
            std::cout << "Line -> " << element.eLine + 1 << " Game Figure -> " << element.eGameFigure + 1 << " Figure Count -> " << element.unFigureCount << " Win -> " << element.fWin << std::endl;
        }
        LOG_WARN("MathLogic - KidsFantasy - Win Element END ");
    }
}

void MathLogic::GenerateDemoResults(Matrix2DResults &arrResults)
{
    /*Clear container with wins*/
    m_vectorWins.clear();

    /*Get Given Results*/
    m_arrResults = arrResults;

    /*Here is just a print logic*/
    LOG_WARN("MathLogic - KidsFantasy - Generated Results BEGIN ");
    for (unsigned int figure = GameDefs::eFirstPositionNONVisible; figure < GameDefs::eTotalFigurePositionsPerReel; ++figure)
    {
        for (unsigned int reel = GameDefs::eFirstReel; reel < GameDefs::eTotalReelCount; ++reel)
        {
            std::cout << m_arrResults[figure][reel] + 1 << "   ";
        }

        std::cout << std::endl;
    }
    LOG_WARN("MathLogic - KidsFantasy - Generated Results END ");

    /*Check for Lines win*/
    CheckForWins();

    /*Here is just a print logic of the lines*/
    if (!m_vectorWins.empty())
    {
        LOG_WARN("MathLogic - KidsFantasy - Win Element BEGIN ");
        for (const auto &element : m_vectorWins)
        {
            std::cout << "MathLogic - KidsFantasy - Line -> " << element.eLine + 1 << " Game Figure -> " << element.eGameFigure + 1 << " Figure Count -> " << element.unFigureCount << " Win -> " << element.fWin << std::endl;
        }
        LOG_WARN("MathLogic - KidsFantasy - Win Element END ");
    }
}

void MathLogic::PushWinElementInContainer(const GameDefs::ELines eLine, const GameDefs::EGameFigure eGameFigure, const unsigned int unFigureCount, const float fWinFromFigure)
{
    m_vectorWins.emplace_back(WinElement{eLine, eGameFigure, unFigureCount, fWinFromFigure});
}

void MathLogic::CheckForWins()
{
    /*Check for Lines*/
    for (unsigned int currentLine = GameDefs::eLine1; currentLine < GameDefs::eTotalLinesCount; ++currentLine)
    {
        const auto &arrLineFigures = GameDefs::g_arrLines.at(currentLine);
        unsigned int unWinFiguresCount = 1;

        for (unsigned int reel = GameDefs::eFirstReel; reel < GameDefs::eTotalReelCount - 1; ++reel)
        {
            unsigned int unCurrentReel = reel;
            unsigned int unNextReel = reel + 1;
            unsigned int unCurrentFigurePosition = arrLineFigures.at(unCurrentReel);
            unsigned int unNexFigurePosition = arrLineFigures.at(unNextReel);

            GameDefs::EGameFigure eCurrentFigure = m_arrResults[unCurrentFigurePosition][unCurrentReel];
            GameDefs::EGameFigure eNextReelFigure = m_arrResults[unNexFigurePosition][unNextReel];

            if (eCurrentFigure == eNextReelFigure)
            {
                ++unWinFiguresCount;

                if (unWinFiguresCount == GameDefs::eTotalReelCount)
                {
                    const float fWinFromFigures = GameDefs::g_arrWinFiguresPay.at(eCurrentFigure).at(unWinFiguresCount - 1) * MainApp::GetInstance().ptrPanel->GetCurrentBet();
                    PushWinElementInContainer((GameDefs::ELines)currentLine, eCurrentFigure, unWinFiguresCount, fWinFromFigures);
                }
            }
            else
            {
                if (unWinFiguresCount >= GameDefs::g_unMinFiguresNeededToFormWin)
                {
                    const float fWinFromFigures = GameDefs::g_arrWinFiguresPay.at(eCurrentFigure).at(unWinFiguresCount - 1) * MainApp::GetInstance().ptrPanel->GetCurrentBet();
                    PushWinElementInContainer((GameDefs::ELines)currentLine, eCurrentFigure, unWinFiguresCount, fWinFromFigures);
                }

                break;
            }
        }
    }
}

const Matrix2DResults &MathLogic::GetResults()
{
    return m_arrResults;
}

const std::vector<WinElement> &MathLogic::GetWinElements()
{
    return m_vectorWins;
}

const float MathLogic::GetWinFromCurrentGame()
{
    float fWinFromGame = 0.0f;

    if (ThereIsAWin())
    {
        for (auto &winElement : m_vectorWins)
        {
            fWinFromGame += roundf(winElement.fWin * 100) / 100;
        }
    }

    return fWinFromGame;
}