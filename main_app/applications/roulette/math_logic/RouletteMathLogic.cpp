#include "RouletteMathLogic.h"

#include <cstdlib>
#include <iostream>
#include <main_app/panel/Panel.h>
#include <debug/Logger.h>

RouletteMathLogic::RouletteMathLogic()
{
}

RouletteMathLogic::~RouletteMathLogic()
{
}

bool RouletteMathLogic::Init()
{
    FillContainerWinSectors();

    LOG_INFO("MathLogic - Roulette - Initialized ...");
    return true;
}

bool RouletteMathLogic::Deinit()
{
    ResetValuesToWinSector();
    LOG_WARN("MathLogic - Roulette - Deinitialized ...");
    return true;
}

void RouletteMathLogic::FillContainerWinSectors()
{
    for (unsigned int i = 0; i < GameDefs::EWheelSectors::eTotalWheelSectorsCount; ++i)
    {
        AssingValuesToWinSector(i);
        m_arrWinSectors.at(i) = m_winSector;
    }

    ResetValuesToWinSector();
}

void RouletteMathLogic::GenerateResults(int unDemoSectorNumber)
{
    LOG_WARN("MathLogic - Roulette - Generated Results BEGIN ");

    /*Generate random number in range (0, 37]*/
    unsigned int unGeneratedNumber = GenerateRandomNumber(GameDefs::EWheelSectors::eSector32, GameDefs::EWheelSectors::eTotalWheelSectorsCount);

    /*If there is number different from -1 (if there is demo sector number)*/
    if (unDemoSectorNumber != -1)
    {
        if (unDemoSectorNumber < 0 || unDemoSectorNumber > 36)
        {
            LOG_CRITICAL("MathLogic - Roulette - Invalid Demo Sector Number : \"{0}\"", unDemoSectorNumber);
        }
        else
        {
            unGeneratedNumber = unDemoSectorNumber;
            std::cout << "DEMO Sector Number : " << unGeneratedNumber << std::endl;
        }
    }

    /*Assing values*/
    AssingValuesToWinSector(unGeneratedNumber);

    /*Check for win called here*/
    CheckForWins();

    LOG_WARN("MathLogic - Roulette - Generated Results END ");
}

unsigned int RouletteMathLogic::CheckSumSectorElements(GameDefs::ETableElements eSectorElement)
{
    unsigned int unSumToReturn = 0;

    const auto &sectorElements = m_matrixInGameBetElements.at(eSectorElement);
    if (!sectorElements.empty())
    {
        for (auto &element : sectorElements)
        {
            unSumToReturn += element;
        }

        std::cout << "Sum of elements found : " << unSumToReturn << std::endl;
    }

    return unSumToReturn;
}

void RouletteMathLogic::CheckForWins()
{
    /*Just print logic*/
    std::cout << "Winning Sector - " << m_winSector.eWinningSector << std::endl;

    /*Numbers*/
    if (m_winSector.unWinningSectorNumber == 0)
    {
        std::cout << "IS ZERO !!!" << std::endl;
        unsigned int unWinFromNumber = CheckSumSectorElements((GameDefs::ETableElements)m_winSector.unWinningSectorNumber);

        m_unTotalWinFromGame += (unWinFromNumber * GameDefs::g_unCoeffNumber);
    }
    else
    {
        std::cout << "Winning Sector NUMBER - " << m_winSector.unWinningSectorNumber << std::endl;
        unsigned int unWinFromNumber = CheckSumSectorElements((GameDefs::ETableElements)m_winSector.unWinningSectorNumber);

        m_unTotalWinFromGame += (unWinFromNumber * GameDefs::g_unCoeffNumber);
    }

    /*Color*/
    if (m_winSector.eColor == GameDefs::ETableElements::eRed)
    {
        std::cout << "Winning Sector COLOR - "
                  << "Red" << std::endl;

        unsigned int unWinFromRedColor = CheckSumSectorElements(GameDefs::ETableElements::eRed);

        m_unTotalWinFromGame += (unWinFromRedColor * GameDefs::g_unCoeffRedBlack);
    }
    else if (m_winSector.eColor == GameDefs::ETableElements::eBlack)
    {
        std::cout << "Winning Sector COLOR - "
                  << "Black" << std::endl;

        unsigned int unWinFromBlackColor = CheckSumSectorElements(GameDefs::ETableElements::eBlack);

        m_unTotalWinFromGame += (unWinFromBlackColor * GameDefs::g_unCoeffRedBlack);
    }

    /*Even - Odd*/
    if (m_winSector.eEvenOdd == GameDefs::ETableElements::eEven)
    {
        std::cout << "Winning Sector EVEN/ODD - "
                  << "Even" << std::endl;

        unsigned int unWinFromEvenOdd = CheckSumSectorElements(GameDefs::ETableElements::eEven);

        m_unTotalWinFromGame += (unWinFromEvenOdd * GameDefs::g_unCoeffEvenOdd);
    }
    else if (m_winSector.eEvenOdd == GameDefs::ETableElements::eOdd)
    {
        std::cout << "Winning Sector EVEN/ODD - "
                  << "Odd" << std::endl;

        unsigned int unWinFromEvenOdd = CheckSumSectorElements(GameDefs::ETableElements::eOdd);

        m_unTotalWinFromGame += (unWinFromEvenOdd * GameDefs::g_unCoeffEvenOdd);
    }

    /*Twelfth*/
    if (m_winSector.eTwelfth == GameDefs::ETableElements::e1st12)
    {
        std::cout << "Winning Sector TWELFTH - "
                  << "1st 12" << std::endl;

        unsigned int unWinFromTwefth = CheckSumSectorElements(GameDefs::ETableElements::e1st12);

        m_unTotalWinFromGame += (unWinFromTwefth * GameDefs::g_unCoeffTwelfth);
    }
    else if (m_winSector.eTwelfth == GameDefs::ETableElements::e2nd12)
    {
        std::cout << "Winning Sector TWELFTH - "
                  << "2nd 12" << std::endl;

        unsigned int unWinFromTwefth = CheckSumSectorElements(GameDefs::ETableElements::e2nd12);

        m_unTotalWinFromGame += (unWinFromTwefth * GameDefs::g_unCoeffTwelfth);
    }
    else if (m_winSector.eTwelfth == GameDefs::ETableElements::e3rd12)
    {
        std::cout << "Winning Sector TWELFTH - "
                  << "3rd 12" << std::endl;
        unsigned int unWinFromTwefth = CheckSumSectorElements(GameDefs::ETableElements::e3rd12);

        m_unTotalWinFromGame += (unWinFromTwefth * GameDefs::g_unCoeffTwelfth);
    }

    /*By Three*/
    if (m_winSector.eByThree == GameDefs::ETableElements::e1By3)
    {
        std::cout << "Winning Sector BY THREE - "
                  << "1 by 3" << std::endl;

        unsigned int unWinFromByThree = CheckSumSectorElements(GameDefs::ETableElements::e1By3);

        m_unTotalWinFromGame += (unWinFromByThree * GameDefs::g_unCoeffByThree);
    }
    else if (m_winSector.eByThree == GameDefs::ETableElements::e2By3)
    {
        std::cout << "Winning Sector BY THREE - "
                  << "2 by 3" << std::endl;

        unsigned int unWinFromByThree = CheckSumSectorElements(GameDefs::ETableElements::e2By3);

        m_unTotalWinFromGame += (unWinFromByThree * GameDefs::g_unCoeffByThree);
    }
    else if (m_winSector.eByThree == GameDefs::ETableElements::e3By3)
    {
        std::cout << "Winning Sector BY THREE - "
                  << "3 by 3" << std::endl;

        unsigned int unWinFromByThree = CheckSumSectorElements(GameDefs::ETableElements::e3By3);

        m_unTotalWinFromGame += (unWinFromByThree * GameDefs::g_unCoeffByThree);
    }

    /*Half Table*/
    if (m_winSector.eHalfTable == GameDefs::ETableElements::e1to18)
    {
        std::cout << "Winning Sector HALF TABLE - "
                  << "1 to 18" << std::endl;

        unsigned int unWinFromHalfTable = CheckSumSectorElements(GameDefs::ETableElements::e1to18);

        m_unTotalWinFromGame += (unWinFromHalfTable * GameDefs::g_unCoeffHalfTable);
    }
    else if (m_winSector.eHalfTable == GameDefs::ETableElements::e19to36)
    {
        std::cout << "Winning Sector HALF TABLE - "
                  << "19 to 36" << std::endl;

        unsigned int unWinFromHalfTable = CheckSumSectorElements(GameDefs::ETableElements::e19to36);

        m_unTotalWinFromGame += (unWinFromHalfTable * GameDefs::g_unCoeffHalfTable);
    }

    std::cout << "Total Win From Game (after coeff multiplication)-> " << m_unTotalWinFromGame << std::endl;
    /*****************/
}

void RouletteMathLogic::InsertInGameElement(const GameDefs::ETableElements eAtElement, unsigned int unValueToInsert)
{
    m_matrixInGameBetElements.at(eAtElement).emplace_back(unValueToInsert);

    LOG_WARN("MathLogic - Roulette - Inserted  at Game Element \"{0}\" value \"{1}\"", eAtElement, unValueToInsert);
}

void RouletteMathLogic::AssingValuesToWinSector(const unsigned int &unGeneratedNumber)
{
    /*Assing the generated random number to the winning sector*/
    m_winSector.eWinningSector = (GameDefs::EWheelSectors)unGeneratedNumber;

    /*Assing the winnin sector value*/
    m_winSector.unWinningSectorNumber = GameDefs::g_arrSectorNumbers.at(unGeneratedNumber);

    switch (m_winSector.eWinningSector)
    {

    case GameDefs::EWheelSectors::eSector0:
    {
        m_winSector.eColor = GameDefs::ETableElements::eZero;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eZero;
        m_winSector.eTwelfth = GameDefs::ETableElements::eZero;
        m_winSector.eByThree = GameDefs::ETableElements::eZero;
        m_winSector.eHalfTable = GameDefs::ETableElements::eZero;
    }
    break;

    case GameDefs::EWheelSectors::eSector1:
    {
        m_winSector.eColor = GameDefs::ETableElements::eRed;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eOdd;
        m_winSector.eTwelfth = GameDefs::ETableElements::e1st12;
        m_winSector.eByThree = GameDefs::ETableElements::e1By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector2:
    {
        m_winSector.eColor = GameDefs::ETableElements::eBlack;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eEven;
        m_winSector.eTwelfth = GameDefs::ETableElements::e1st12;
        m_winSector.eByThree = GameDefs::ETableElements::e2By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector3:
    {
        m_winSector.eColor = GameDefs::ETableElements::eRed;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eOdd;
        m_winSector.eTwelfth = GameDefs::ETableElements::e1st12;
        m_winSector.eByThree = GameDefs::ETableElements::e3By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector4:
    {
        m_winSector.eColor = GameDefs::ETableElements::eBlack;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eEven;
        m_winSector.eTwelfth = GameDefs::ETableElements::e1st12;
        m_winSector.eByThree = GameDefs::ETableElements::e1By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector5:
    {
        m_winSector.eColor = GameDefs::ETableElements::eRed;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eOdd;
        m_winSector.eTwelfth = GameDefs::ETableElements::e1st12;
        m_winSector.eByThree = GameDefs::ETableElements::e2By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector6:
    {
        m_winSector.eColor = GameDefs::ETableElements::eBlack;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eEven;
        m_winSector.eTwelfth = GameDefs::ETableElements::e1st12;
        m_winSector.eByThree = GameDefs::ETableElements::e3By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector7:
    {
        m_winSector.eColor = GameDefs::ETableElements::eRed;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eOdd;
        m_winSector.eTwelfth = GameDefs::ETableElements::e1st12;
        m_winSector.eByThree = GameDefs::ETableElements::e1By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector8:
    {
        m_winSector.eColor = GameDefs::ETableElements::eBlack;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eEven;
        m_winSector.eTwelfth = GameDefs::ETableElements::e1st12;
        m_winSector.eByThree = GameDefs::ETableElements::e2By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector9:
    {
        m_winSector.eColor = GameDefs::ETableElements::eRed;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eOdd;
        m_winSector.eTwelfth = GameDefs::ETableElements::e1st12;
        m_winSector.eByThree = GameDefs::ETableElements::e3By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector10:
    {
        m_winSector.eColor = GameDefs::ETableElements::eBlack;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eEven;
        m_winSector.eTwelfth = GameDefs::ETableElements::e1st12;
        m_winSector.eByThree = GameDefs::ETableElements::e1By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector11:
    {
        m_winSector.eColor = GameDefs::ETableElements::eBlack;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eOdd;
        m_winSector.eTwelfth = GameDefs::ETableElements::e1st12;
        m_winSector.eByThree = GameDefs::ETableElements::e2By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector12:
    {
        m_winSector.eColor = GameDefs::ETableElements::eRed;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eEven;
        m_winSector.eTwelfth = GameDefs::ETableElements::e1st12;
        m_winSector.eByThree = GameDefs::ETableElements::e3By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector13:
    {
        m_winSector.eColor = GameDefs::ETableElements::eBlack;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eOdd;
        m_winSector.eTwelfth = GameDefs::ETableElements::e2nd12;
        m_winSector.eByThree = GameDefs::ETableElements::e1By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector14:
    {
        m_winSector.eColor = GameDefs::ETableElements::eRed;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eEven;
        m_winSector.eTwelfth = GameDefs::ETableElements::e2nd12;
        m_winSector.eByThree = GameDefs::ETableElements::e2By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector15:
    {
        m_winSector.eColor = GameDefs::ETableElements::eBlack;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eOdd;
        m_winSector.eTwelfth = GameDefs::ETableElements::e2nd12;
        m_winSector.eByThree = GameDefs::ETableElements::e3By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector16:
    {
        m_winSector.eColor = GameDefs::ETableElements::eRed;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eEven;
        m_winSector.eTwelfth = GameDefs::ETableElements::e2nd12;
        m_winSector.eByThree = GameDefs::ETableElements::e1By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector17:
    {
        m_winSector.eColor = GameDefs::ETableElements::eBlack;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eOdd;
        m_winSector.eTwelfth = GameDefs::ETableElements::e2nd12;
        m_winSector.eByThree = GameDefs::ETableElements::e2By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector18:
    {
        m_winSector.eColor = GameDefs::ETableElements::eRed;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eEven;
        m_winSector.eTwelfth = GameDefs::ETableElements::e2nd12;
        m_winSector.eByThree = GameDefs::ETableElements::e3By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector19:
    {
        m_winSector.eColor = GameDefs::ETableElements::eRed;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eOdd;
        m_winSector.eTwelfth = GameDefs::ETableElements::e2nd12;
        m_winSector.eByThree = GameDefs::ETableElements::e1By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector20:
    {
        m_winSector.eColor = GameDefs::ETableElements::eBlack;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eEven;
        m_winSector.eTwelfth = GameDefs::ETableElements::e2nd12;
        m_winSector.eByThree = GameDefs::ETableElements::e2By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector21:
    {
        m_winSector.eColor = GameDefs::ETableElements::eRed;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eOdd;
        m_winSector.eTwelfth = GameDefs::ETableElements::e2nd12;
        m_winSector.eByThree = GameDefs::ETableElements::e3By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector22:
    {
        m_winSector.eColor = GameDefs::ETableElements::eBlack;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eEven;
        m_winSector.eTwelfth = GameDefs::ETableElements::e2nd12;
        m_winSector.eByThree = GameDefs::ETableElements::e1By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector23:
    {
        m_winSector.eColor = GameDefs::ETableElements::eRed;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eOdd;
        m_winSector.eTwelfth = GameDefs::ETableElements::e2nd12;
        m_winSector.eByThree = GameDefs::ETableElements::e2By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector24:
    {
        m_winSector.eColor = GameDefs::ETableElements::eBlack;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eEven;
        m_winSector.eTwelfth = GameDefs::ETableElements::e2nd12;
        m_winSector.eByThree = GameDefs::ETableElements::e3By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector25:
    {
        m_winSector.eColor = GameDefs::ETableElements::eRed;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eOdd;
        m_winSector.eTwelfth = GameDefs::ETableElements::e3rd12;
        m_winSector.eByThree = GameDefs::ETableElements::e1By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector26:
    {
        m_winSector.eColor = GameDefs::ETableElements::eBlack;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eEven;
        m_winSector.eTwelfth = GameDefs::ETableElements::e3rd12;
        m_winSector.eByThree = GameDefs::ETableElements::e2By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector27:
    {
        m_winSector.eColor = GameDefs::ETableElements::eRed;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eOdd;
        m_winSector.eTwelfth = GameDefs::ETableElements::e3rd12;
        m_winSector.eByThree = GameDefs::ETableElements::e3By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector28:
    {
        m_winSector.eColor = GameDefs::ETableElements::eBlack;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eEven;
        m_winSector.eTwelfth = GameDefs::ETableElements::e3rd12;
        m_winSector.eByThree = GameDefs::ETableElements::e1By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector29:
    {
        m_winSector.eColor = GameDefs::ETableElements::eBlack;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eOdd;
        m_winSector.eTwelfth = GameDefs::ETableElements::e3rd12;
        m_winSector.eByThree = GameDefs::ETableElements::e2By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector30:
    {
        m_winSector.eColor = GameDefs::ETableElements::eRed;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eEven;
        m_winSector.eTwelfth = GameDefs::ETableElements::e3rd12;
        m_winSector.eByThree = GameDefs::ETableElements::e3By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector31:
    {
        m_winSector.eColor = GameDefs::ETableElements::eBlack;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eOdd;
        m_winSector.eTwelfth = GameDefs::ETableElements::e3rd12;
        m_winSector.eByThree = GameDefs::ETableElements::e1By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector32:
    {
        m_winSector.eColor = GameDefs::ETableElements::eRed;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eEven;
        m_winSector.eTwelfth = GameDefs::ETableElements::e3rd12;
        m_winSector.eByThree = GameDefs::ETableElements::e2By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector33:
    {
        m_winSector.eColor = GameDefs::ETableElements::eBlack;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eOdd;
        m_winSector.eTwelfth = GameDefs::ETableElements::e3rd12;
        m_winSector.eByThree = GameDefs::ETableElements::e3By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector34:
    {
        m_winSector.eColor = GameDefs::ETableElements::eRed;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eEven;
        m_winSector.eTwelfth = GameDefs::ETableElements::e3rd12;
        m_winSector.eByThree = GameDefs::ETableElements::e1By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector35:
    {
        m_winSector.eColor = GameDefs::ETableElements::eBlack;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eOdd;
        m_winSector.eTwelfth = GameDefs::ETableElements::e3rd12;
        m_winSector.eByThree = GameDefs::ETableElements::e2By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector36:
    {
        m_winSector.eColor = GameDefs::ETableElements::eRed;
        m_winSector.eEvenOdd = GameDefs::ETableElements::eEven;
        m_winSector.eTwelfth = GameDefs::ETableElements::e3rd12;
        m_winSector.eByThree = GameDefs::ETableElements::e3By3;
        m_winSector.eHalfTable = GameDefs::ETableElements::e19to36;
    }
    break;

    default:
        LOG_WARN("MathLogic - Roulette - INVALID Sector ");
        ResetValuesToWinSector();
        break;
    }
}

void RouletteMathLogic::ResetValuesToWinSector()
{
    m_unTotalWinFromGame = 0;
    m_winSector.eWinningSector = GameDefs::EWheelSectors::eSector0;
    m_winSector.unWinningSectorNumber = 36;
    m_winSector.eColor = GameDefs::ETableElements::eZero;
    m_winSector.eEvenOdd = GameDefs::ETableElements::eZero;
    m_winSector.eTwelfth = GameDefs::ETableElements::eZero;
    m_winSector.eByThree = GameDefs::ETableElements::eZero;
    m_winSector.eHalfTable = GameDefs::ETableElements::eZero;

    for (auto &element : m_matrixInGameBetElements)
    {
        element.clear();
    }

    LOG_WARN("MathLogic - Roulette - RESET Wins ");
}

const bool RouletteMathLogic::IsAnyInGameElement()
{
    bool bIsAnyElement = false;

    for (const auto &element : m_matrixInGameBetElements)
    {
        if (!element.empty())
        {
            bIsAnyElement = true;
            break;
        }
    }
    return bIsAnyElement;
}

const GameDefs::EWheelSectors &RouletteMathLogic::GetWinningSector()
{
    return m_winSector.eWinningSector;
}

const unsigned int &RouletteMathLogic::GetWinningSectorNumber()
{
    return m_winSector.unWinningSectorNumber;
}

const unsigned int &RouletteMathLogic::GetTotalWinFromGame()
{
    return m_unTotalWinFromGame;
}

const GameDefs::ETableElements &RouletteMathLogic::GetWinningSectorColor()
{
    return m_winSector.eColor;
}

const WinSector &RouletteMathLogic::GetCurrentWinningSector()
{
    return m_winSector;
}

const std::array<WinSector, GameDefs::eTotalWheelSectorsCount> &RouletteMathLogic::GetContainerWinSectors()
{
    return m_arrWinSectors;
}

long RouletteMathLogic::GenerateRandomNumber(long nLowerBound, long nUpperBound)
{
    unsigned int unSeed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(unSeed);
    long nNumberToReturn = rand() % nUpperBound + nLowerBound;

    // LOG_INFO("MathLogic - Roulette - Generated Random Number - \"{0}\"", nNumberToReturn);

    return nNumberToReturn;
}