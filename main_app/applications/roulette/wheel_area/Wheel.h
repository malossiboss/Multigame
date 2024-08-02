#pragma once

#include <main_app/texture/Texture.h>
#include <main_app/timer/TimerMgr.h>
#include <main_app/interpolator/Interpolator.h>

enum class EWheelStates
{
    eStopped,
    eRotatingSlow,
    eRotatingFast,
    eDecrementingToZero,
    eTotalWheelStates
};

class Wheel : public ITimer
{
private:
    /*Wheel State*/
    EWheelStates m_eState = EWheelStates::eStopped;

    /*Degrees Wheel*/
    float m_fDegreesWheel = 0.0f;

    /*Speed Wheel*/
    float m_fSpeedWheel = 0.0f;

    /*Check in which sector we are*/
    unsigned int m_unCounterSector = 0;

    /*Texture Wheel Table*/
    std::shared_ptr<Texture> m_textureWheelTable;

    /*Texture Wheel*/
    std::shared_ptr<Texture> m_textureWheel;

    /*Texture Wheel Shadow*/
    std::shared_ptr<Texture> m_textureWheelShadow;

    /*Interpolator acceleration*/
    Interpolator m_interpolatorAcceleration;

    /*Interpolator decceleration*/
    Interpolator m_interpolatorDecceleration;

    /*Callback called when wheel stopped*/
    std::function<void()> m_wheelStoppedCallback;

    /*Method that check if angle > 360*/
    void NormalizeAngle();

public:
    bool Init();
    bool Deinit();
    void Draw();
    void StartSlowRotation();
    void DecrementSlowRotationToZero();
    void StopRotation();
    void StartFastRotation();
    void DecrementToSlowRotation();
    void OnTick(unsigned int unID, unsigned int unTimes) final;
    void SetWheelStoppedCallback(std::function<void()> &wheelStoppedCallback);
    const EWheelStates &GetState();
    const float &GetSpeed();
    const float &GetDegrees();
};