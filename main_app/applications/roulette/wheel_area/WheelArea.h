#pragma once

#include "Wheel.h"
#include "Ball.h"

class WheelArea : public ITimer
{
private:

    /*Ball Object*/
    Ball m_Ball;

    /*Wheel Object*/
    Wheel m_Wheel;

    /*Method called when AfterSpinningStopped() gets called, due to notification in MainGame*/
    std::function<void()>m_afterSpinningStoppedCallback;

    /*Callback, called after stop of the ball*/
    void AfterSpinningStopped();

    /*Callback, called after wheel stopped*/
    void AfterWheelStopped();

public:
    bool Init();
    bool Deinit();
    bool HandleEvent();
    void Draw();
    void StartSlowRotation();
    void StopRotation();
    void OnTick(unsigned int unID, unsigned int unTimes) final;
    /*Method called when need to start new spin*/
    bool StartNewSpin(int nDemoSectorNumber = -1);
    void SetAfterSpinningStoppedCallback(std::function<void()>& afterSpinningStoppedCallback);
};