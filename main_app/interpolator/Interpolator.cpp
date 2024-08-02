#include "Interpolator.h"

#include <main_app/MainApp.h>
#include <debug/Logger.h>

const unsigned int g_unTimerProcess = 1;
const unsigned int g_unTimerProcessPeriod = 1;

void Interpolator::Start(float &fCurrentValue, float fInitialValue, float fDestValue, Ease easingFunction, unsigned int unDurationInMilliSeconds)
{
    m_fProgress = 0.0f;
    m_fDeltaTime = MainApp::GetInstance().GetDeltaTime();
    m_fCurrentValue = &fCurrentValue;
    m_fInitialValue = fInitialValue;
    m_fDestValue = fDestValue;
    m_easingFunction = easingFunction;
    m_unDurationInMilliSeconds = unDurationInMilliSeconds;

    MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerProcess, g_unTimerProcessPeriod);
    m_eState = EInterpolatorStates::eInProgress;
}

void Interpolator::Stop(bool bReachDestValue)
{
    if (bReachDestValue)
    {
        m_fCurrentValue = &m_fDestValue;
    }

    m_fProgress = 0.0f;
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unTimerProcess);
    m_eState = EInterpolatorStates::eInactive;
}

void Interpolator::Pause()
{
    if (m_eState == EInterpolatorStates::eInProgress)
    {
        m_eState = EInterpolatorStates::ePaused;
    }
}

void Interpolator::Resume()
{
    if (m_eState == EInterpolatorStates::ePaused)
    {
        m_eState = EInterpolatorStates::eInProgress;
    }
}

void Interpolator::OnTick(unsigned int unID, unsigned int unTimes)
{
    if (unID == g_unTimerProcess)
    {
        if (m_eState == EInterpolatorStates::ePaused)
        {
            return;
        }

        Progress();
    }
}

void Interpolator::Progress()
{
    const float fStepsToReachDestTime = (float)m_unDurationInMilliSeconds / m_fDeltaTime;
    const float fIncrementStep = 1.0f / fStepsToReachDestTime;

    m_fProgress += fIncrementStep;
    if (m_fProgress >= 1.0f)
    {
        m_fProgress = 1.0f;
    }

    switch (m_easingFunction)
    {

    case Ease::Linear:
        *m_fCurrentValue = Easing::LinearEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::QuadraticIn:
        *m_fCurrentValue = Easing::QuadraticInEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::QuadraticOut:
        *m_fCurrentValue = Easing::QuadraticOutEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::QuadraticInOut:
        *m_fCurrentValue = Easing::QuadraticInOutEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::CubicIn:
        *m_fCurrentValue = Easing::CubicInEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::CubicOut:
        *m_fCurrentValue = Easing::CubicOutEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::CubicInOut:
        *m_fCurrentValue = Easing::CubicInOutEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::SineIn:
        *m_fCurrentValue = Easing::SineInEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::SineOut:
        *m_fCurrentValue = Easing::SineOutEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::SineInOut:
        *m_fCurrentValue = Easing::SineInOutEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::ExponentialIn:
        *m_fCurrentValue = Easing::ExponentialInEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::ExponentialOut:
        *m_fCurrentValue = Easing::ExponentialOutEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::ExponentialInOut:
        *m_fCurrentValue = Easing::ExponentialInOutEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::CircularIn:
        *m_fCurrentValue = Easing::CircularInEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::CircularOut:
        *m_fCurrentValue = Easing::CircularOutEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::CircularInOut:
        *m_fCurrentValue = Easing::CircularInOutEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::BounceIn:
        *m_fCurrentValue = Easing::BounceInEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::BounceOut:
        *m_fCurrentValue = Easing::BounceOutEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::BounceInOut:
        *m_fCurrentValue = Easing::BounceInOutEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::ElasticIn:
        *m_fCurrentValue = Easing::ElasticInEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::ElasticOut:
        *m_fCurrentValue = Easing::ElasticOutEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    case Ease::ElasticInOut:
        *m_fCurrentValue = Easing::ElasticInOutEasing(m_fProgress, m_fInitialValue, m_fDestValue);
        break;

    default:
        LOG_ERROR("Interpolator - No such of Easing Function !");
        break;
    }

    if (m_fProgress == 1.0f)
    {
        Stop();

        if (m_endCallback)
        {
            m_endCallback();
        }
    }
}

void Interpolator::SetEndCallback(std::function<void()> &endCallback)
{
    m_endCallback = endCallback;
}

const float &Interpolator::GetProgress()
{
    return m_fProgress;
}

const EInterpolatorStates &Interpolator::GetState()
{
    return m_eState;
}