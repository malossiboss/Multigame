#include "TableArea.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/applications/roulette/math_logic/RouletteMathLogic.h>
#include <main_app/MainApp.h>
#include <main_app/panel/Panel.h>
#include <main_app/renderer/Renderer.h>
#include <main_app/audio_player/AudioPlayer.h>
#include <debug/Logger.h>

constexpr float g_fXTableBets = 920.0f;
constexpr float g_fYTableBets = 300.0f;

constexpr float g_fXOffsetFromBetChips = 170.0f;
constexpr float g_fXOffsetBetChips = 30.0f;
constexpr float g_fYOffsetBetChips = -100.0f;
constexpr float g_fXOffsetBethipsTable = 3.0f;
constexpr float g_fYOffsetBethipsTable = -121.0f;

const float g_fAlphaElementsPattern = 0.6f;

constexpr float g_fYMaxBetChips = g_fYTableBets + g_fYOffsetBetChips - 80.0f;
constexpr float g_fYMinBetChips = g_fYTableBets + g_fYOffsetBetChips;

constexpr float g_fXWinningDest = 1400.0f;
constexpr float g_fYWinningDest = 970.0f;

constexpr float g_fXLoosingDest = 1400.0f;
constexpr float g_fYLoosingDest = -100.0f;

constexpr unsigned int g_unDurationCollectEffectChips = 1000;

const std::array<glm::vec2, GameDefs::eTotalTableElements> g_arrTableElements =
    {
        {
            {0, 0},     /* 0 */
            {98, 181},  /* 1 */
            {98, 93},   /* 2 */
            {98, 6},    /* 3 */
            {163, 181}, /* 4 */
            {163, 93},  /* 5 */
            {163, 6},   /* 6 */
            {229, 181}, /* 7 */
            {229, 93},  /* 8 */
            {229, 6},   /* 9 */
            {294, 181}, /* 10 */
            {294, 93},  /* 11 */
            {294, 6},   /* 12 */
            {359, 181}, /* 13 */
            {359, 93},  /* 14 */
            {359, 6},   /* 15 */
            {424, 181}, /* 16 */
            {424, 93},  /* 17 */
            {424, 6},   /* 18 */
            {489, 181}, /* 19 */
            {489, 93},  /* 20 */
            {489, 6},   /* 21 */
            {554, 181}, /* 22 */
            {554, 93},  /* 23 */
            {554, 6},   /* 24 */
            {619, 181}, /* 25 */
            {619, 93},  /* 26 */
            {619, 6},   /* 27 */
            {684, 181}, /* 28 */
            {684, 93},  /* 29 */
            {684, 6},   /* 30 */
            {749, 181}, /* 31 */
            {749, 93},  /* 32 */
            {749, 6},   /* 33 */
            {815, 181}, /* 34 */
            {815, 93},  /* 35 */
            {815, 6},   /* 36 */
            {881, 181}, /* 1by3 */
            {881, 93},  /* 2by3 */
            {881, 6},   /* 3by3 */
            {98, 269},  /* 1st12 */
            {359, 269}, /* 2nd12 */
            {619, 269}, /* 3rd12 */
            {98, 340},  /* 1to18 */
            {229, 340}, /* Even */
            {359, 340}, /* Red */
            {489, 340}, /* Black */
            {619, 340}, /* Odd */
            {749, 340}  /* 19to36 */
        }};

void Chip::StartCollectEffect(const float fXDest, const float fYDest, unsigned int unSpeedMultiplier)
{
    eState = EChipState::eAnimatingEndGame;

    std::function<void()> endCallback = [this]()
    {
        eState = EChipState::eInactive;
    };

    interpolatorAfterGameAnimX.SetEndCallback(endCallback);

    interpolatorAfterGameAnimX.Start(buttonChip.fX, buttonChip.fX, fXDest, Ease::CircularIn, g_unDurationCollectEffectChips + unSpeedMultiplier);
    interpolatorAfterGameAnimY.Start(buttonChip.fY, buttonChip.fY, fYDest, Ease::CircularIn, g_unDurationCollectEffectChips + unSpeedMultiplier);
}

void Chip::StartFadeEffect(unsigned int unSpeedMultiplier)
{
    eState = EChipState::eAnimatingEndGame;

    std::function<void()> endCallback = [this]()
    {
        eState = EChipState::eInactive;
    };

    interpolatorFade.SetEndCallback(endCallback);
    interpolatorFade.Start(buttonChip.colorButton.a, 1.0f, 0.0f, Ease::CircularIn, g_unDurationCollectEffectChips + unSpeedMultiplier);
}

bool TableArea::Init()
{
    m_textureTableBets = Texture::CreateTexture("../src/resources/roulette/table_bets/table_bets.png");
    m_textureChipsTable = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_table.png");
    m_textureZeroPattern = Texture::CreateTexture("../src/resources/roulette/table_bets/zero_pattern.png");
    m_textureNumbersPattern = Texture::CreateTexture("../src/resources/roulette/table_bets/numbers_pattern.png");
    m_textureTwelvePattern = Texture::CreateTexture("../src/resources/roulette/table_bets/twelve_pattern.png");
    m_textureDownerPattern = Texture::CreateTexture("../src/resources/roulette/table_bets/down_pattern.png");
    m_textureChipShadow = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_shadow.png");

    m_arrBetChips.at(GameDefs::eChip_1).buttonChip.textureButton = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_1.png");
    m_arrBetChips.at(GameDefs::eChip_5).buttonChip.textureButton = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_5.png");
    m_arrBetChips.at(GameDefs::eChip_10).buttonChip.textureButton = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_10.png");
    m_arrBetChips.at(GameDefs::eChip_25).buttonChip.textureButton = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_25.png");
    m_arrBetChips.at(GameDefs::eChip_100).buttonChip.textureButton = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_100.png");
    m_arrBetChips.at(GameDefs::eChip_500).buttonChip.textureButton = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_500.png");

    m_arrBetChips.at(GameDefs::eChip_1).buttonChip.fValue = 1.0f;
    m_arrBetChips.at(GameDefs::eChip_5).buttonChip.fValue = 5.0f;
    m_arrBetChips.at(GameDefs::eChip_10).buttonChip.fValue = 10.0f;
    m_arrBetChips.at(GameDefs::eChip_25).buttonChip.fValue = 25.0f;
    m_arrBetChips.at(GameDefs::eChip_100).buttonChip.fValue = 100.0f;
    m_arrBetChips.at(GameDefs::eChip_500).buttonChip.fValue = 500.0f;

    if (!m_textureTableBets->Load())
    {
        LOG_ERROR("TableArea - Unable to load texture table bets !");
        return false;
    }

    if (!m_textureChipsTable->Load())
    {
        LOG_ERROR("TableArea - Unable to load texture chips table !");
        return false;
    }

    if (!m_textureZeroPattern->Load())
    {
        LOG_ERROR("TableArea - Unable to load texture zero pattern !");
        return false;
    }

    if (!m_textureNumbersPattern->Load())
    {
        LOG_ERROR("TableArea - Unable to load texture numbers pattern !");
        return false;
    }

    if (!m_textureTwelvePattern->Load())
    {
        LOG_ERROR("TableArea - Unable to load texture twelve pattern !");
        return false;
    }

    if (!m_textureDownerPattern->Load())
    {
        LOG_ERROR("TableArea - Unable to load texture down pattern !");
        return false;
    }

    if (!m_textureChipShadow->Load())
    {
        LOG_ERROR("TableArea - Unable to load texture chip shadow!");
        return false;
    }

    /*Sectors - Table Elements*/
    m_arrTableElements.at(GameDefs::eZero).buttonSector.fValue = 0.0f;
    m_arrTableElements.at(GameDefs::eZero).buttonSector.textureButton = m_textureZeroPattern;
    m_arrTableElements.at(GameDefs::eZero).buttonSector.fX = g_arrTableElements.at(GameDefs::eZero).x + g_fXTableBets;
    m_arrTableElements.at(GameDefs::eZero).buttonSector.fY = g_arrTableElements.at(GameDefs::eZero).y + g_fYTableBets;

    for (unsigned int i = GameDefs::eOne; i <= GameDefs::e3By3; ++i)
    {
        m_arrTableElements.at(i).buttonSector.fValue = i;
        m_arrTableElements.at(i).buttonSector.textureButton = m_textureNumbersPattern;
        m_arrTableElements.at(i).buttonSector.fX = g_arrTableElements.at(i).x + g_fXTableBets;
        m_arrTableElements.at(i).buttonSector.fY = g_arrTableElements.at(i).y + g_fYTableBets;
    }
    for (unsigned int i = GameDefs::e1st12; i <= GameDefs::e3rd12; ++i)
    {
        m_arrTableElements.at(i).buttonSector.fValue = i;
        m_arrTableElements.at(i).buttonSector.textureButton = m_textureTwelvePattern;
        m_arrTableElements.at(i).buttonSector.fX = g_arrTableElements.at(i).x + g_fXTableBets;
        m_arrTableElements.at(i).buttonSector.fY = g_arrTableElements.at(i).y + g_fYTableBets;
    }
    for (unsigned int i = GameDefs::e1to18; i <= GameDefs::e19to36; ++i)
    {
        m_arrTableElements.at(i).buttonSector.fValue = i;
        m_arrTableElements.at(i).buttonSector.textureButton = m_textureDownerPattern;
        m_arrTableElements.at(i).buttonSector.fX = g_arrTableElements.at(i).x + g_fXTableBets;
        m_arrTableElements.at(i).buttonSector.fY = g_arrTableElements.at(i).y + g_fYTableBets;
    }

    for (auto &element : m_arrTableElements)
    {
        element.buttonSector.colorButton.a = g_fAlphaElementsPattern;
    }

    /*Table Bets*/
    m_buttonTableBets.textureButton = m_textureTableBets;
    m_buttonTableBets.fX = g_fXTableBets;
    m_buttonTableBets.fY = g_fYTableBets;

    /*Chips*/
    for (unsigned int i = 0; i < m_arrBetChips.size(); ++i)
    {
        auto &chip = m_arrBetChips[i];

        if (!chip.buttonChip.textureButton->Load())
        {
            LOG_ERROR("TableArea - Unable to load texture chip !");
            return false;
        }

        chip.buttonChip.fX = g_fXTableBets + g_fXOffsetBetChips + (g_fXOffsetFromBetChips * i);
        chip.buttonChip.fY = g_fYTableBets + g_fYOffsetBetChips;
    }

    /*Reserve at every element at least 100 spaces, due to optimization*/
    for (auto &element : m_arrTableElements)
    {
        element.vecOnSectorChips.reserve(100);
    }

    LOG_INFO("Table Area - Initialized ...");
    return true;
}

bool TableArea::Deinit()
{
    LOG_WARN("Table Area - Deinitialized ...");
    return true;
}

bool TableArea::HandleEvent()
{
    const auto &nXMouse = ImGui::GetMousePos().x;
    const auto &nYMouse = ImGui::GetMousePos().y;
    const auto &fAvalableCredit = MainApp::GetInstance().ptrPanel->GetAvailableCredit();

    for (unsigned int i = 0; i < GameDefs::eTotalCountChips; ++i)
    {
        auto &chip = m_arrBetChips[i];
        /*If credit available, unlock chips*/
        if ((fAvalableCredit < chip.buttonChip.fValue) || m_bLockBetTable)
        {
            chip.buttonChip.colorButton.a = 0.3f;
            chip.buttonChip.bIsLocked = true;
            chip.eState = EChipState::eLocked;
            continue;
        }

        chip.buttonChip.bIsLocked = false;
        chip.eState = EChipState::eReadyForSelection;

        /*Press / Release Chip*/
        if (chip.buttonChip.IsReleased(nXMouse, nYMouse))
        {
            /*Hover on invalid sector*/
            if (m_eCurrentHoverTableElement == GameDefs::ETableElements::eTotalTableElements)
            {
                /*When released, reset position to the dragged chip from table*/
                chip.buttonChip.fX = g_fXTableBets + g_fXOffsetBetChips + (g_fXOffsetFromBetChips * i);
                chip.buttonChip.fY = g_fYTableBets + g_fYOffsetBetChips;

                chip.bIsSelectedForBet = false;
                m_bIsAnyChipSelected = false;
                chip.eState = EChipState::eReadyForSelection;
                break;
            }

            chip.eState = EChipState::eReleasedToSector;
            chip.bIsSelectedForBet = false;
            m_bIsAnyChipSelected = false;

            /*When released, create object chip and push it to the sector container*/
            auto &tableSector = m_arrTableElements[m_eCurrentHoverTableElement];

            /*Create and emplace here, due to later use the vector reference object*/
            Chip chipToEmplace;
            chipToEmplace.buttonChip.textureButton = chip.buttonChip.textureButton;
            chipToEmplace.buttonChip.fValue = chip.buttonChip.fValue;
            chipToEmplace.eState = EChipState::eReleasedToSector;
            chipToEmplace.bIsSelectedForBet = false;
            chipToEmplace.buttonChip.colorButton.a = 1.0f;

            const auto &fXMiddleSector = tableSector.buttonSector.fX + (tableSector.buttonSector.textureButton->GetWidth() / 2);
            const auto &fYMiddleSector = tableSector.buttonSector.fY + (tableSector.buttonSector.textureButton->GetHeight() / 2);

            float fXDest = fXMiddleSector - (GameDefs::g_fWidthBetChip / 2) + ((tableSector.vecOnSectorChips.size()) * 5);
            float fYDest = fYMiddleSector - (GameDefs::g_fHeightBetChip / 2) - ((tableSector.vecOnSectorChips.size()) * 5);

            /*Actual release effect of the chip*/
            chipToEmplace.buttonChip.fX = fXDest;
            chipToEmplace.buttonChip.fY = fYDest;

            RouletteMathLogic::GetInstance().InsertInGameElement(m_eCurrentHoverTableElement, chipToEmplace.buttonChip.fValue);
            MainApp::GetInstance().ptrPanel->RemoveCredit(chipToEmplace.buttonChip.fValue);
            tableSector.vecOnSectorChips.emplace_back(chipToEmplace);

            /*When released, reset position to the dragged chip from table*/
            chip.eState = EChipState::eReleasedToSector;
            chip.buttonChip.fX = g_fXTableBets + g_fXOffsetBetChips + (g_fXOffsetFromBetChips * i);
            chip.buttonChip.fY = g_fYTableBets + g_fYOffsetBetChips;

            MainApp::GetInstance().ptrAudioPlayer->PlaySound("../src/resources/roulette/sounds/release_chip.wav");

            LOG_INFO("Table Area - Released chip with value \"{0}\" at Sector \"{1}\", total elements on Sector \"{2}\"",
                     chipToEmplace.buttonChip.fValue,
                     m_eCurrentHoverTableElement,
                     tableSector.vecOnSectorChips.size());
        }
        else if (chip.bIsSelectedForBet || chip.buttonChip.IsPressed(nXMouse, nYMouse))
        {
            chip.eState = EChipState::eSelected;
            chip.bIsSelectedForBet = true;
            m_bIsAnyChipSelected = true;

            chip.buttonChip.colorButton.a = 0.5f;
            chip.buttonChip.fX = nXMouse - (chip.buttonChip.textureButton->GetWidth() / 2);
            chip.buttonChip.fY = nYMouse - (chip.buttonChip.textureButton->GetHeight() / 2);

            if (chip.buttonChip.IsPressed(nXMouse, nYMouse))
            {
                MainApp::GetInstance().ptrAudioPlayer->PlaySound("../src/resources/roulette/sounds/take_chip.wav");
            }
        }
        /*Hover on Chip*/
        else if (chip.buttonChip.IsHovered(nXMouse, nYMouse))
        {
            chip.buttonChip.colorButton.a = 1.0f;
        }
        else
        {
            chip.buttonChip.colorButton.a = 0.7f;
        }
    }

    /*Table Elements*/
    if (m_bIsAnyChipSelected)
    {
        m_eCurrentHoverTableElement = GameDefs::ETableElements::eTotalTableElements;
        for (unsigned int i = GameDefs::eZero; i < GameDefs::eTotalTableElements; ++i)
        {
            auto &element = m_arrTableElements[i];
            if (element.buttonSector.IsHovered(nXMouse, nYMouse))
            {
                m_eCurrentHoverTableElement = (GameDefs::ETableElements)i;
                element.buttonSector.colorButton.a = 0.0f;
            }
            else
            {
                element.buttonSector.colorButton.a = g_fAlphaElementsPattern;
            }
        }

        /*1st12 Hovered*/
        if (m_arrTableElements[GameDefs::e1st12].buttonSector.IsHovered(nXMouse, nYMouse))
        {
            for (unsigned int i = GameDefs::eOne; i <= GameDefs::eTwelve; ++i)
            {
                auto &sector = m_arrTableElements[i];
                sector.buttonSector.colorButton.a = 0.0f;
            }
        }

        /*2nd12 Hovered*/
        else if (m_arrTableElements[GameDefs::e2nd12].buttonSector.IsHovered(nXMouse, nYMouse))
        {
            for (unsigned int i = GameDefs::eThirteen; i <= GameDefs::eTwentyFour; ++i)
            {
                auto &sector = m_arrTableElements[i];
                sector.buttonSector.colorButton.a = 0.0f;
            }
        }

        /*3rd12 Hovered*/
        else if (m_arrTableElements[GameDefs::e3rd12].buttonSector.IsHovered(nXMouse, nYMouse))
        {
            for (unsigned int i = GameDefs::eTwentyFive; i <= GameDefs::eThirtySix; ++i)
            {
                auto &sector = m_arrTableElements[i];
                sector.buttonSector.colorButton.a = 0.0f;
            }
        }

        /*1to18 Hovered*/
        else if (m_arrTableElements[GameDefs::e1to18].buttonSector.IsHovered(nXMouse, nYMouse))
        {
            for (unsigned int i = GameDefs::eOne; i <= GameDefs::eEighteen; ++i)
            {
                auto &sector = m_arrTableElements[i];
                sector.buttonSector.colorButton.a = 0.0f;
            }
        }

        /*Even Hovered*/
        else if (m_arrTableElements[GameDefs::eEven].buttonSector.IsHovered(nXMouse, nYMouse))
        {
            for (unsigned int i = GameDefs::eOne; i <= GameDefs::eThirtySix; ++i)
            {
                auto &sector = m_arrTableElements[i];
                if ((int)sector.buttonSector.fValue % 2 == 0)
                {
                    sector.buttonSector.colorButton.a = 0.0f;
                }
            }
        }

        /*Odd Hovered*/
        else if (m_arrTableElements[GameDefs::eOdd].buttonSector.IsHovered(nXMouse, nYMouse))
        {
            for (unsigned int i = GameDefs::eOne; i <= GameDefs::eThirtySix; ++i)
            {
                auto &sector = m_arrTableElements[i];
                if ((int)sector.buttonSector.fValue % 2)
                {
                    sector.buttonSector.colorButton.a = 0.0f;
                }
            }
        }

        /*19to36 Hovered*/
        else if (m_arrTableElements[GameDefs::e19to36].buttonSector.IsHovered(nXMouse, nYMouse))
        {
            for (unsigned int i = GameDefs::eNineteen; i <= GameDefs::eThirtySix; ++i)
            {
                auto &sector = m_arrTableElements[i];
                sector.buttonSector.colorButton.a = 0.0f;
            }
        }

        /*Red Hovered*/
        else if (m_arrTableElements[GameDefs::eRed].buttonSector.IsHovered(nXMouse, nYMouse))
        {
            std::vector<unsigned int> vecRedSectors;
            for (auto &winSector : RouletteMathLogic::GetInstance().GetContainerWinSectors())
            {
                if (winSector.eColor == GameDefs::ETableElements::eRed)
                {
                    vecRedSectors.emplace_back(winSector.unWinningSectorNumber);
                }
            }

            for (auto &redSector : vecRedSectors)
            {
                auto &sector = m_arrTableElements[redSector];
                sector.buttonSector.colorButton.a = 0.0f;
            }
        }

        /*Black Hovered*/
        else if (m_arrTableElements[GameDefs::eBlack].buttonSector.IsHovered(nXMouse, nYMouse))
        {
            std::vector<unsigned int> vecBlackSectors;
            for (auto &winSector : RouletteMathLogic::GetInstance().GetContainerWinSectors())
            {
                if (winSector.eColor == GameDefs::ETableElements::eBlack)
                {
                    vecBlackSectors.emplace_back(winSector.unWinningSectorNumber);
                }
            }

            for (auto &blackSector : vecBlackSectors)
            {
                auto &sector = m_arrTableElements[blackSector];
                sector.buttonSector.colorButton.a = 0.0f;
            }
        }

        /*1by3 Hovered*/
        else if (m_arrTableElements[GameDefs::e1By3].buttonSector.IsHovered(nXMouse, nYMouse))
        {
            std::vector<unsigned int> vecBy3Sectors;
            for (auto &winSector : RouletteMathLogic::GetInstance().GetContainerWinSectors())
            {
                if (winSector.eByThree == GameDefs::ETableElements::e1By3)
                {
                    vecBy3Sectors.emplace_back(winSector.unWinningSectorNumber);
                }
            }

            for (auto &by3Sector : vecBy3Sectors)
            {
                auto &sector = m_arrTableElements[by3Sector];
                sector.buttonSector.colorButton.a = 0.0f;
            }
        }

        /*2by3 Hovered*/
        else if (m_arrTableElements[GameDefs::e2By3].buttonSector.IsHovered(nXMouse, nYMouse))
        {
            std::vector<unsigned int> vecBy3Sectors;
            for (auto &winSector : RouletteMathLogic::GetInstance().GetContainerWinSectors())
            {
                if (winSector.eByThree == GameDefs::ETableElements::e2By3)
                {
                    vecBy3Sectors.emplace_back(winSector.unWinningSectorNumber);
                }
            }

            for (auto &by3Sector : vecBy3Sectors)
            {
                auto &sector = m_arrTableElements[by3Sector];
                sector.buttonSector.colorButton.a = 0.0f;
            }
        }

        /*3by3 Hovered*/
        else if (m_arrTableElements[GameDefs::e3By3].buttonSector.IsHovered(nXMouse, nYMouse))
        {
            std::vector<unsigned int> vecBy3Sectors;
            for (auto &winSector : RouletteMathLogic::GetInstance().GetContainerWinSectors())
            {
                if (winSector.eByThree == GameDefs::ETableElements::e3By3)
                {
                    vecBy3Sectors.emplace_back(winSector.unWinningSectorNumber);
                }
            }

            for (auto &by3Sector : vecBy3Sectors)
            {
                auto &sector = m_arrTableElements[by3Sector];
                sector.buttonSector.colorButton.a = 0.0f;
            }
        }
    }

    return false;
}

bool TableArea::IsEndGameScenarioFinished()
{
    for (const auto &element : m_arrTableElements)
    {
        for (const auto &chip : element.vecOnSectorChips)
        {
            if (chip.eState != EChipState::eInactive)
            {
                return false;
            }
        }
    }

    return true;
}

void TableArea::LockBetTable()
{
    m_bLockBetTable = true;
}

void TableArea::UnlockBetTable()
{
    m_bLockBetTable = false;
}

void TableArea::StartWinAnimations()
{
    WinSector currentWinSector = RouletteMathLogic::GetInstance().GetCurrentWinningSector();

    for (unsigned int i = GameDefs::ETableElements::eZero; i < GameDefs::ETableElements::eTotalTableElements; ++i)
    {
        auto &tableElement = m_arrTableElements[i];

        /*If there is chips on sector, check sector if winning*/
        if (tableElement.vecOnSectorChips.empty())
        {
            continue;
        }
        else
        {

            /*Check Wins*/
            if (tableElement.buttonSector.fValue == currentWinSector.unWinningSectorNumber ||
                tableElement.buttonSector.fValue == currentWinSector.eColor ||
                tableElement.buttonSector.fValue == currentWinSector.eEvenOdd ||
                tableElement.buttonSector.fValue == currentWinSector.eTwelfth ||
                tableElement.buttonSector.fValue == currentWinSector.eByThree ||
                tableElement.buttonSector.fValue == currentWinSector.eHalfTable)
            {
                unsigned int unSpeedMultiplier = 0;
                for (auto &chips : tableElement.vecOnSectorChips)
                {
                    chips.StartCollectEffect(g_fXWinningDest, g_fYWinningDest, unSpeedMultiplier);
                    unSpeedMultiplier += 200;
                }

                MainApp::GetInstance().ptrAudioPlayer->PlaySound("../src/resources/roulette/sounds/applause_short.wav");
            }
            else
            {
                unsigned int unSpeedMultiplier = 0;
                for (auto &chips : tableElement.vecOnSectorChips)
                {
                    chips.StartFadeEffect(unSpeedMultiplier);
                    unSpeedMultiplier += 200;
                }
            }
        }
    }
}

void TableArea::ResetTableElements()
{
    for (auto &element : m_arrTableElements)
    {
        for (auto &chip : element.vecOnSectorChips)
        {
            chip.interpolatorAfterGameAnimX.Stop();
            chip.interpolatorAfterGameAnimY.Stop();
            chip.interpolatorFade.Stop();
        }
        element.vecOnSectorChips.clear();
    }

    LOG_INFO("Table Area - Reset Table Elements");
}

void TableArea::Draw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    /*Draw Table Bets*/
    rend->SetColor(m_buttonTableBets.colorButton.r,
                   m_buttonTableBets.colorButton.g,
                   m_buttonTableBets.colorButton.b,
                   m_buttonTableBets.colorButton.a);
    rend->DrawPicture(m_buttonTableBets.textureButton, m_buttonTableBets.fX, m_buttonTableBets.fY);
    rend->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

    /*Draw On Table Game Chips*/
    for (auto &sectorElement : m_arrTableElements)
    {
        unsigned int unChipCount = 1;
        const float fOffsetShadow = 8.0f;
        const float fDegreesShadow = -40.0f;
        for (auto &chip : sectorElement.vecOnSectorChips)
        {
            float fAlphShadow = chip.buttonChip.colorButton.a - (0.6 + (0.04f * unChipCount));
            rend->SetColor(1.0f,
                           1.0f,
                           1.0f,
                           fAlphShadow);
            rend->DrawPictureRotated(m_textureChipShadow, chip.buttonChip.fX - (fOffsetShadow * unChipCount), chip.buttonChip.fY - (fOffsetShadow * unChipCount), fDegreesShadow);
            rend->SetColor(chip.buttonChip.colorButton.r,
                           chip.buttonChip.colorButton.g,
                           chip.buttonChip.colorButton.b,
                           chip.buttonChip.colorButton.a);
            rend->DrawPicture(chip.buttonChip.textureButton, chip.buttonChip.fX, chip.buttonChip.fY);
            rend->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
            ++unChipCount;
        }
    }

    /*Draw Patterns Table Elements*/
    if (m_bIsAnyChipSelected)
    {
        for (auto &element : m_arrTableElements)
        {
            rend->SetColor(element.buttonSector.colorButton.r,
                           element.buttonSector.colorButton.g,
                           element.buttonSector.colorButton.b,
                           element.buttonSector.colorButton.a);
            rend->DrawPicture(element.buttonSector.textureButton, element.buttonSector.fX, element.buttonSector.fY);
            rend->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
        }
    }

    /*Chips Table*/
    rend->DrawPicture(m_textureChipsTable, g_fXTableBets + g_fXOffsetBethipsTable, g_fYTableBets + g_fYOffsetBethipsTable);

    /*Draw Bet Chip*/
    for (auto &chip : m_arrBetChips)
    {
        rend->SetColor(chip.buttonChip.colorButton.r,
                       chip.buttonChip.colorButton.g,
                       chip.buttonChip.colorButton.b,
                       chip.buttonChip.colorButton.a);
        rend->DrawPicture(chip.buttonChip.textureButton, chip.buttonChip.fX, chip.buttonChip.fY);
        rend->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
}