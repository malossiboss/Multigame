#pragma once
#include <vector>
#include <main_app/applications/kids_fantasy/GameDefinitions.h>

typedef std::array<std::array<GameDefs::EGameFigure, GameDefs::eTotalFigurePositionsPerReel>, GameDefs::eTotalReelCount> Matrix2DResults;

struct WinElement
{
    GameDefs::ELines eLine;
    GameDefs::EGameFigure eGameFigure;
    unsigned int unFigureCount;
    float fWin = 0.0f;
};

class MathLogic
{

private:

    MathLogic();
    ~MathLogic();

    /*2D matrix 5x5 holding game results*/
    Matrix2DResults m_arrResults;

    /*Container holding win elements from current game*/
    std::vector<WinElement>m_vectorWins;

    /*Pushes Current win element in m_vectorWins*/
    void PushWinElementInContainer(const GameDefs::ELines eLine, const GameDefs::EGameFigure eGameFigure, const unsigned int unFigureCount, const float fWinFromFigure);

    /*Method check for wins AFTER results has been generated*/
    void CheckForWins();

public:


    static MathLogic& GetInstance()
    {
        static MathLogic mathLogic;
        return mathLogic;
    }

    /** Delete copyt-constructor, move-constructor and assignment operators */
    MathLogic(MathLogic const&) = delete;
    void operator = (MathLogic const&) = delete;
    MathLogic(MathLogic &&) = delete;
    void operator = (MathLogic &&) = delete;

    bool Init();
    bool Deinit();

    /*Returns true, if there is a win*/
    bool ThereIsAWin();

    /*Method that generates results in the current game*/
    void GenerateResults();

    /*Method used in Demo Mode*/
    void GenerateDemoResults(Matrix2DResults& arrResults);

    /*Returns m_arrResults matrix, DO NOT FORGET TO CALL GenerateResults() !*/
    const Matrix2DResults& GetResults();

    /*Returns m_vectorWins container*/
    const std::vector<WinElement>& GetWinElements();

    /*Returns total win from current game*/
    const float GetWinFromCurrentGame();

    /*Returns a random number in the interval (0, 10]*/
    long GenerateRandomNuber(long nLowerBoundOpenInterval, long nUpperBoundClosedInterval);

};