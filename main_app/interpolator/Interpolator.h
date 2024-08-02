#pragma once
#include "Easing.h"

#include <functional>

#include <main_app/timer/TimerMgr.h>

enum class EInterpolatorStates
{
    eInactive,
    eInProgress,
    ePaused
};

class Interpolator : public ITimer
{

private:
    float *m_fCurrentValue;
    float m_fInitialValue;
    float m_fDestValue;
    float m_fProgress;
    float m_fDeltaTime;
    EInterpolatorStates m_eState = EInterpolatorStates::eInactive;
    Ease m_easingFunction;
    unsigned int m_unDurationInMilliSeconds;
    std::function<void()> m_endCallback;

    void Progress();

public:
    void Start(float &fCurrentValue, float fInitialValue, float fDestValue, Ease easingFunction, unsigned int unDurationInMilliSeconds);
    void Stop(bool bReachDestValue = true);
    void Pause();
    void Resume();
    void OnTick(unsigned int unID, unsigned int unTimes) final;
    void SetEndCallback(std::function<void()> &endCallback);
    const float &GetProgress();
    const EInterpolatorStates& GetState();
};