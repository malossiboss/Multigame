#pragma once

#include <vector>

#include <main_app/applications/roulette/GameDefinitions.h>
#include <main_app/interpolator/Interpolator.h>
#include <main_app/texture/Texture.h>
#include <main_app/button/Button.h>

enum class EChipState
{
    eInactive,
    eLocked,
    eReadyForSelection,
    eSelected,
    eReleasedToSector,
    eAnimatingEndGame,
    eTotalChipStates
};

struct Chip
{
    EChipState eState = EChipState::eInactive;
    bool bIsSelectedForBet = false;
    Interpolator interpolatorAfterGameAnimX;
    Interpolator interpolatorAfterGameAnimY;
    Interpolator interpolatorFade;
    Button buttonChip;

    /*Win Effect*/
    void StartCollectEffect(const float fXDest, const float fYDest, unsigned int unSpeedMultiplier = 0);

    /*Fade Effect, lose*/
    void StartFadeEffect( unsigned int unSpeedMultiplier = 0);
};

struct Sector
{
    std::vector<Chip> vecOnSectorChips;
    Button buttonSector;
};

class TableArea
{
private:
    /*True if any chip selected*/
    bool m_bIsAnyChipSelected = false;

    /*Lock bet buttons for be selected*/
    bool m_bLockBetTable = false;

    /*Texture Table Bets*/
    std::shared_ptr<Texture> m_textureTableBets;

    /*Texture Chips Table*/
    std::shared_ptr<Texture> m_textureChipsTable;

    /*Texture Zero Pattern*/
    std::shared_ptr<Texture> m_textureZeroPattern;

    /*Texture Numbers Pattern*/
    std::shared_ptr<Texture> m_textureNumbersPattern;

    /*Texture Twelve Pattern*/
    std::shared_ptr<Texture> m_textureTwelvePattern;

    /*Texture Downer Pattern*/
    std::shared_ptr<Texture> m_textureDownerPattern;

    /*Texture Chip Shadow*/
    std::shared_ptr<Texture> m_textureChipShadow;

    /*Container holding textures buttons of bet chips*/
    std::array<Chip, GameDefs::eTotalCountChips> m_arrBetChips;

    /*Container holding all the table elements*/
    std::array<Sector, GameDefs::eTotalTableElements> m_arrTableElements;

    /*Change in base of currently hover element*/
    GameDefs::ETableElements m_eCurrentHoverTableElement = GameDefs::eTotalTableElements;

    /*Fade effect table bets when hovered*/
    Interpolator m_interpolatorFadeInTableBets;
    Interpolator m_interpolatorFadeOutTableBets;

    /*Button Bet Table, used just to use the Hover logic*/
    Button m_buttonTableBets;

public:
    bool Init();
    bool Deinit();
    bool HandleEvent();
    bool IsEndGameScenarioFinished();
    void LockBetTable();
    void UnlockBetTable();
    void StartWinAnimations();
    void ResetTableElements();
    void Draw();
};