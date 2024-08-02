#pragma once

#include <array>

namespace GameDefs
{
    constexpr unsigned int g_unCoeffRedBlack = 2;
    constexpr unsigned int g_unCoeffEvenOdd = 2;
    constexpr unsigned int g_unCoeffHalfTable = 2;
    constexpr unsigned int g_unCoeffTwelfth = 3;
    constexpr unsigned int g_unCoeffByThree = 3;
    constexpr unsigned int g_unCoeffNumber = 36;

    constexpr float g_fWidthBallRoulette = 26.0f;
    constexpr float g_fHeightBallRoulette = 26.0f;

    constexpr float g_fWidthBetChip = 70.0f;
    constexpr float g_fHeightBetChip = 70.0f;

    constexpr float g_fAnglePerSector = 9.73f;

    constexpr float g_fSlowSpeedWheel = 0.1f;
    constexpr float g_fFastSpeedWheel = 0.1f;

    constexpr unsigned int g_unAccelerationSlowSpeedDuration = 1000;
    constexpr unsigned int g_unDecelerationSlowSpeedDuration = 200;

    enum EChips
    {
        eChip_1,
        eChip_5,
        eChip_10,
        eChip_25,
        eChip_100,
        eChip_500,
        eTotalCountChips
    };

    const std::array<unsigned int, eTotalCountChips> g_arrChipsValue =
        {
            1,
            5,
            10,
            25,
            100,
            500};

    enum EWheelSectors
    {
        eSector32,
        eSector15,
        eSector19,
        eSector4,
        eSector21,
        eSector2,
        eSector25,
        eSector17,
        eSector34,
        eSector6,
        eSector27,
        eSector13,
        eSector36,
        eSector11,
        eSector30,
        eSector8,
        eSector23,
        eSector10,
        eSector5,
        eSector24,
        eSector16,
        eSector33,
        eSector1,
        eSector20,
        eSector14,
        eSector31,
        eSector9,
        eSector22,
        eSector18,
        eSector29,
        eSector7,
        eSector28,
        eSector12,
        eSector35,
        eSector3,
        eSector26,
        eSector0,
        eTotalWheelSectorsCount
    };

    const std::array<unsigned int, eTotalWheelSectorsCount> g_arrSectorNumbers =
        {
            32,
            15,
            19,
            4,
            21,
            2,
            25,
            17,
            34,
            6,
            27,
            13,
            36,
            11,
            30,
            8,
            23,
            10,
            5,
            24,
            16,
            33,
            1,
            20,
            14,
            31,
            9,
            22,
            18,
            29,
            7,
            28,
            12,
            35,
            3,
            26,
            0};

    enum ETableElements
    {
        eZero,
        eOne,
        eTwo,
        eThree,
        eFour,
        eFive,
        eSix,
        eSeven,
        eEight,
        eNine,
        eTen,
        eEleven,
        eTwelve,
        eThirteen,
        eFourteen,
        eFiftheen,
        eSixteen,
        eSeventeen,
        eEighteen,
        eNineteen,
        eTwenty,
        eTwentyOne,
        eTwentyTwo,
        eTwentyThree,
        eTwentyFour,
        eTwentyFive,
        eTwentySix,
        eTwentySeven,
        eTwentyEight,
        eTwentyNine,
        eThirty,
        eThirtyOne,
        eThirtyTwo,
        eThirtyThree,
        eThirtyFour,
        eThirtyFive,
        eThirtySix,
        e1By3,
        e2By3,
        e3By3,
        e1st12,
        e2nd12,
        e3rd12,
        e1to18,
        eEven,
        eRed,
        eBlack,
        eOdd,
        e19to36,
        eTotalTableElements
    };
}