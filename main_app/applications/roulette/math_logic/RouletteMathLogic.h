#pragma once

#include <vector>
#include <main_app/applications/roulette/GameDefinitions.h>

struct WinSector
{
    GameDefs::EWheelSectors eWinningSector = GameDefs::EWheelSectors::eSector0;
    unsigned int unWinningSectorNumber = 36;
    GameDefs::ETableElements eColor = GameDefs::ETableElements::eZero;
    GameDefs::ETableElements eEvenOdd = GameDefs::ETableElements::eZero;
    GameDefs::ETableElements eTwelfth = GameDefs::ETableElements::eZero;
    GameDefs::ETableElements eByThree = GameDefs::ETableElements::eZero;
    GameDefs::ETableElements eHalfTable = GameDefs::ETableElements::eZero;
};

class RouletteMathLogic
{

private:
    RouletteMathLogic();
    ~RouletteMathLogic();

    /*Holding total win from current game*/
    unsigned int m_unTotalWinFromGame = 0;

    /*Container with all the winning sectors*/
    std::array<WinSector, GameDefs::eTotalWheelSectorsCount> m_arrWinSectors;

    /*Container holding all the bets element when chip released, elements inserted*/
    std::array<std::vector<unsigned int>, GameDefs::ETableElements::eTotalTableElements> m_matrixInGameBetElements;

    /*Win Sector Object, generated in every new game*/
    WinSector m_winSector;

    /*Method called at Init*/
    void FillContainerWinSectors();

    /*Assing all values when number generated*/
    void AssingValuesToWinSector(const unsigned int &unGeneratedNumber);

    /*Check and returns the sum of the sector elements if there is any*/
    unsigned int CheckSumSectorElements(GameDefs::ETableElements eSectorElement);

public:
    static RouletteMathLogic &GetInstance()
    {
        static RouletteMathLogic mathLogic;
        return mathLogic;
    }

    /** Delete copyt-constructor, move-constructor and assignment operators */
    RouletteMathLogic(RouletteMathLogic const &) = delete;
    void operator=(RouletteMathLogic const &) = delete;
    RouletteMathLogic(RouletteMathLogic &&) = delete;
    void operator=(RouletteMathLogic &&) = delete;

    bool Init();
    bool Deinit();

    /*Method that generates results in the current game*/
    void GenerateResults(int unDemoSectorNumber = -1);

    /*Method that check for wins after generates results is called*/
    void CheckForWins();

    /*Method that inserts all bets element when chip released*/
    void InsertInGameElement(const GameDefs::ETableElements eAtElement, unsigned int unValueToInsert);

    /*Reset all values to zero*/
    void ResetValuesToWinSector();

    /*Return true if there is any chip on table*/
    const bool IsAnyInGameElement();

    /*Returns m_winSector.eWinningSector*/
    const GameDefs::EWheelSectors &GetWinningSector();

    /*Returns m_winSector.unWinningSectorNumber*/
    const unsigned int &GetWinningSectorNumber();

    /*Returns m_unTotalWinFromGame*/
    const unsigned int &GetTotalWinFromGame();

    /*Returns m_winSector.eColor*/
    const GameDefs::ETableElements &GetWinningSectorColor();

    /*Returns m_winSector object*/
    const WinSector& GetCurrentWinningSector();

    /*Returns container with all winning sectors*/
    const std::array<WinSector, GameDefs::eTotalWheelSectorsCount> &GetContainerWinSectors();

    /*Returns a random number in the interval (0, 10]*/
    long GenerateRandomNumber(long nLowerBoundOpenInterval, long nUpperBoundClosedInterval);
};