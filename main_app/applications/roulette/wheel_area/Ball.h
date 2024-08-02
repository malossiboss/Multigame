#pragma once

#include <main_app/applications/roulette/GameDefinitions.h>
#include <main_app/texture/Texture.h>
#include <main_app/timer/TimerMgr.h>
#include <main_app/interpolator/Interpolator.h>

/*Collision limits in container*/
enum ECollisionLimits
{
    eMinX,
    eMaxX,
    eMinY,
    eMaxY,
    eTotalCollisionLimits
};

enum class EBallStates
{
    eHidden,
    eRotateInTableOrbit,
    eGoingToSector,
    eStoppedAndRotateWithWheel,
    eDecrementingToZero,
    eTotalBallStates
};

class Ball : public ITimer
{

private:
    /*Ball State*/
    EBallStates m_eState = EBallStates::eHidden;

    /*Degrees Ball*/
    float m_fDegreesBall = 0.0f;
    float m_fDegreesBallMemory = 0.0f;

    /*Degrees Wheel Roulette*/
    float m_fDegreesWheelRoulette = 0.0f;

    /*Speed Wheel Roulette*/
    float m_fSpeedWheelRoulette = 0.0f;

    /*Speed Ball*/
    float m_fSpeedBall = 0.0f;

    /*Distance from wheel center*/
    float m_fDistanceFromWheelCenter = 0.0f;

    /*X Cordinate*/
    float m_fXBall = 0.0f;

    /*Y Coordinate*/
    float m_fYBall = 0.0f;

    /*Polar Coordinate X*/
    float m_fXPolarBall = 0.0f;

    /*Polar Coordinate Y*/
    float m_fYPolarBall = 0.0f;

    /*Ball current speed*/
    float m_fCurrentSpeed = 0.0f;

    /*Callback called when ball stopped*/
    std::function<void()> m_afterSpinningStoppedCallback;

    /*Texture Ball*/
    std::shared_ptr<Texture> m_textureBall;

    /*Texture Ball Shadow*/
    std::shared_ptr<Texture> m_textureBallShadow;

    /*Interpolator rotation*/
    Interpolator m_interpolatorRotate;

    /*Interpolator decrement distance, when rotation slows down*/
    Interpolator m_interpolatorDecrementDistance;

    /*Interpolator that simulate throw of the ball*/
    Interpolator m_interpolatorThrowBall;

    /*Interpolator collision, when collision is detected*/
    Interpolator m_interpolatorCollisionJumpX;
    Interpolator m_interpolatorCollisionJumpY;
    Interpolator m_interpolatorCollisionBounceX;
    Interpolator m_interpolatorCollisionBounceY;

    /*Interpolator acceleration to slow speed*/
    Interpolator m_accelerationSlowSpeed;

    /*Interpolator deceleration to zero*/
    Interpolator m_decelerationToZero;

    /*Check whenever there are some collisions*/
    void CheckForCollision();

    /*Starts collision effect*/
    void StartCollision(float fXForce, float fYForce, unsigned int unJumpDuration, unsigned int unBounceDuration);

    /*Draw Shadow ball effect*/
    void DrawShadow();

public:
    bool Init();
    bool Deinit();
    void Draw();
    void StartSpinning(const GameDefs::EWheelSectors& eWheelSectorToStopAt);
    void StartRotationWithWheel();
    void StopRotationWithWheel();
    void OnTick(unsigned int unID, unsigned int unTimes) final;
    void SetDegreesRoulette(const float &fDegreesWheelRoulette);
    void SetSpeedRoulette(const float &fSpeedWheelRoulette);
    void SetAfterSpinningStoppedCallback(std::function<void()> &afterSpinningStoppedCallback);
    const EBallStates& GetState();
};