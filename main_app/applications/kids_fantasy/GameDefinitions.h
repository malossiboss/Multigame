#pragma once
#include <array>

namespace GameDefs
{
    constexpr unsigned int g_unVisibleFiguresPerReel = 3;
    constexpr unsigned int g_unTotalFiguresPerReel = 5;
    constexpr unsigned int g_unMinFiguresNeededToFormWin = 3;

    constexpr float g_fMinBet = 1.00f;
    constexpr float g_fMaxBet = 5.00f;

    constexpr float g_fWidthFigurePicture = 240.0f;
    constexpr float g_fWidthFigurePictureWithFrameOffset = 250.0f;
    constexpr float g_fHeightFigurePicture = 220.0f;

    constexpr float g_fXReelsArea = 25.0;
    constexpr float g_fYReelsArea = 0.0f;

    constexpr float g_fXOrgPosReel1 = 316.0f;
    constexpr float g_fXOrgPosReel2 = 565.0f;
    constexpr float g_fXOrgPosReel3 = 814.0f;
    constexpr float g_fXOrgPosReel4 = 1062.0f;
    constexpr float g_fXOrgPosReel5 = 1311.0f;

    constexpr float g_fYOrgPosReels = 165.0f;

    enum EGameFigure
    {
        eGameFigureOne,
        eGameFigureTwo,
        eGameFigureThree,
        eGameFigureFour,
        eGameFigureFive,
        eGameFigureSix,
        eTotalGameFiguresCount
    };

    enum EReels
    {
        eFirstReel,
        eSecondReel,
        eThirdReel,
        eFourthReel,
        eFifthReel,
        eTotalReelCount
    };

    enum EFigurePositionPerReel
    {
        eFirstPositionNONVisible,
        eSecondPositionVisible,
        eThirdPositionVisible,
        eFourhtPositionVisible,
        eFifthPositionNONVisible,
        eTotalFigurePositionsPerReel
    };

    const std::array<std::array<float, eTotalReelCount>, eTotalGameFiguresCount> g_arrWinFiguresPay =
        {
            {
                {0.0f, 0.0f, 0.05f, 0.10f, 0.15f}, // Figure 1
                {0.0f, 0.0f, 0.10f, 0.20f, 0.30f}, // Figure 2
                {0.0f, 0.0f, 0.15f, 0.30f, 0.60f}, // Figure 3
                {0.0f, 0.0f, 0.20f, 0.40f, 0.90f}, // Figure 4
                {0.0f, 0.0f, 0.25f, 0.50f, 1.20f}, // Figure 5
                {0.0f, 0.0f, 0.30f, 0.60f, 1.50f}  // Figure 6
            }};

    enum ELines
    {
        eLine1 = 0,
        eLine2,
        eLine3,
        eLine4,
        eLine5,
        eLine6,
        eLine7,
        eLine8,
        eLine9,
        eLine10,
        eLine11,
        eLine12,
        eLine13,
        eLine14,
        eLine15,
        eLine16,
        eLine17,
        eLine18,
        eLine19,
        eLine20,
        eLine21,
        eLine22,
        eLine23,
        eLine24,
        eLine25,
        eLine26,
        eLine27,
        eLine28,
        eLine29,
        eLine30,
        eTotalLinesCount
    };

    const std::array<std::array<int, eTotalReelCount>, eTotalLinesCount> g_arrLines =
        {
            {
                {2, 2, 2, 2, 2}, // Line 1
                {1, 1, 1, 1, 1}, // Line 2
                {3, 3, 3, 3, 3}, // Line 3
                {1, 2, 3, 2, 1}, // Line 4
                {3, 2, 1, 2, 3}, // Line 5
                {1, 1, 2, 3, 3}, // Line 6
                {3, 3, 2, 1, 1}, // Line 7
                {2, 1, 2, 3, 2}, // Line 8
                {2, 3, 2, 1, 2}, // Line 9
                {1, 2, 2, 2, 3}, // Line 10
                {3, 2, 2, 2, 1}, // Line 11
                {2, 1, 1, 2, 3}, // Line 12
                {2, 3, 3, 2, 1}, // Line 13
                {2, 2, 1, 2, 3}, // Line 14
                {2, 2, 3, 2, 1}, // Line 15
                {1, 1, 2, 3, 2}, // Line 16
                {3, 3, 2, 1, 2}, // Line 17
                {2, 1, 2, 3, 3}, // Line 18
                {2, 3, 2, 1, 1}, // Line 19
                {1, 1, 1, 2, 3}, // Line 20
                {3, 3, 3, 2, 1}, // Line 21
                {1, 2, 3, 3, 3}, // Line 22
                {3, 2, 1, 1, 1}, // Line 23
                {1, 2, 1, 2, 1}, // Line 24
                {3, 2, 3, 2, 3}, // Line 25
                {1, 2, 2, 2, 1}, // Line 26
                {3, 2, 2, 2, 3}, // Line 27
                {2, 1, 1, 1, 2}, // Line 28
                {2, 3, 3, 3, 2}, // Line 29
                {1, 2, 1, 2, 3}, // Line 30
            }};
}