#pragma once

#include <iomanip>

#include <main_app/texture/Texture.h>
#include <main_app/font/Font.h>
#include <main_app/timer/TimerMgr.h>
#include <main_app/button/Button.h>
#include <main_app/particle_system/ParticleSystem.h>
#include <main_app/interpolator/Interpolator.h>

enum class EPanelInfoScenes
{
    eNoInfoScene = 0,
    eVolumeScene,
    eCreditScene
};

enum ECreditsCalculator
{
    eOne,
    eTwo,
    eFive,
    eTen,
    eTwenty,
    eFifthy,
    eHundred,
    eTwoHundreds,
    eFiveHundreds,
    eTotalCreditsCalculator
};

class Panel : public ITimer
{

private:
    /*Credit Available*/
    float m_fCreditAvailable = 0.0f;

    /*Current bet bet line*/
    float m_fCurrentBet = 0.0f;

    /*Current win from line*/
    float m_fCurrentWin = 0.0f;

    /*Current win to be reached*/
    float m_fWinToBeReached = 0.0f;

    /*Degrees Rotation Volume Knob*/
    float m_fDegreesVolumeKnob = 0.0f;

    /*Volume Valume 0.0f - 1.0f*/
    float m_fVolumeValue = 0.0f;

    /*Alpha channel info window*/
    float m_fAlphaInfoWindow = 0.0f;

    /*Alpha channel bet buttons*/
    float m_fAlphaBetButtons = 0.0f;

    /*Volume Percentage*/
    int m_nVolumePercentage = 0;

    /*Lock bet buttons, if needed*/
    bool m_bLockBetButtons = false;

    bool m_bHideFields = false;

    /*String Credit Available*/
    std::string m_strCreditAvailable;

    /*String Current Bet*/
    std::string m_strCurrentBet;

    /*String Current Win*/
    std::string m_strCurrentWin;

    /*Textures Home Button pressed, released*/
    std::shared_ptr<Texture> m_textureHomeButton;
    std::shared_ptr<Texture> m_textureHomeButtonPressed;

    /*Textures Volume Button, knob volume*/
    std::shared_ptr<Texture> m_textureVolumeButton;
    std::shared_ptr<Texture> m_textureVolumeKnob;

    /*Texture info window*/
    std::shared_ptr<Texture> m_textureInfoWindow;

    /*Texture panel*/
    std::shared_ptr<Texture> m_textureCreditPanel;
    std::shared_ptr<Texture> m_textureCreditPanelPressed;
    std::shared_ptr<Texture> m_textureCreditPanelPressToAdd;
    std::shared_ptr<Texture> m_textureBetPanel;
    std::shared_ptr<Texture> m_textureBetPanelIncrement;
    std::shared_ptr<Texture> m_textureBetPanelIncrementPressed;
    std::shared_ptr<Texture> m_textureBetPanelDecrement;
    std::shared_ptr<Texture> m_textureBetPanelDecrementPressed;
    std::shared_ptr<Texture> m_textureWinPanel;

    /*Texture Exit Calculator Button*/
    std::shared_ptr<Texture> m_textureExitCalculator;
    std::shared_ptr<Texture> m_textureExitCalculatorPressed;

    /*Textures Buttons Value Credit*/
    std::vector<std::shared_ptr<Texture>> m_vecTexturesButtonsValueCredit;
    std::vector<std::shared_ptr<Texture>> m_vecTexturesButtonsValueCreditPressed;

    /*Texture Reset Button*/
    std::shared_ptr<Texture> m_textureResetButton;
    std::shared_ptr<Texture> m_textureResetButtonPressed;

    /*Textures Particle*/
    std::shared_ptr<Texture> m_textureFlowerParticle;
    std::shared_ptr<Texture> m_textureStarParticle;

    /*Font Volume*/
    std::shared_ptr<Font> m_fontVolume;

    /*Home Button*/
    Button m_homeButton;

    /*Volume Knob Button*/
    Button m_volumeKnobButton;

    /*Credit Button - Field*/
    Button m_creditButton;

    /*Bet Button - Field*/
    Button m_betButton;

    /*Decrement Bet Button*/
    Button m_decrementBetButton;

    /*Increment Bet Button*/
    Button m_incrementBetButton;

    /*Exit Calculator Button*/
    Button m_exitCalculatorButton;

    /*Buttons Value Credit*/
    std::vector<Button> m_vecButtonsValueCredit;

    /*Button Reset Credit*/
    Button m_resetCreditButton;

    /*Holding the current Info scene drawed*/
    EPanelInfoScenes m_eInfoScene = EPanelInfoScenes::eNoInfoScene;

    /*Interpolator money counting*/
    Interpolator m_interpolatorCounting;

    /*Effect win field*/
    ParticleSystem m_particleFlower;
    ParticleSystem m_particleStar;
    /*****************/

    /*Method called when loading buttons, inserts elements in containers*/
    bool LoadCalculatorButtons();

    /*Method Draw Credit in base of lenght of digits*/
    void DrawDynamicTextCredit();

    /*Method Draw Win in base of lenght of digits*/
    void DrawDynamicTextWin();

    /*Method Draw Credit Panel*/
    void DrawCreditPanelButton();

    /*Mehtod Draw Bet Panel*/
    void DrawBetPanel();

    /*Mehtod Draw Win Panel*/
    void DrawWinPanel();

    /*Effect particle win panel*/
    void StartEffectParticleWinPanel();
    void StopEffectParticleWinPanel();

    /*String presicion*/
    std::string ToStringPrecision(const float fValue, const int nPrecision = 2);

public:
    bool Init();
    bool Deinit();
    bool HandleEvent();
    bool CanStartNewGame();
    const float &GetCurrentBet();
    const float &GetAvailableCredit();
    const EPanelInfoScenes& GetPanelInfoScene();
    void OnDraw();
    void OnTick(unsigned int unID, unsigned int unTimes) final;
    void StartWinCounting(float fWinToReach);
    void FastCollectCounting();
    void AddCredit(float fCreditToAdd);
    void RemoveCredit(float fCreditToRemove);
    void DecrementCreditWithBet();
    void ResetWin();
    void ResetCredit();
    void LockBetButtons();
    void UnlockBetButtons();
    void HideFields();
    void ShowFields();
};