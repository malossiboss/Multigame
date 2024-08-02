#include "Wheel.h"

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <main_app/applications/roulette/GameDefinitions.h>
#include <debug/Logger.h>

constexpr float g_fXWheelTable = 0.0f;
constexpr float g_fYWheelTable = 0.0f;

constexpr float g_fXWheelOffset = 134.0f;
constexpr float g_fYWheelOffset = 134.0f;

constexpr float g_fXShadowOffset = 8.0f;
constexpr float g_fYShadowOffset = 15.0f;

constexpr unsigned int g_unAccelerationDecrementSpeedDuration = 3000;

constexpr unsigned int g_unTimerRotationWheel = 1;
constexpr unsigned int g_unTimerRotationWheelPeriod = 1;

bool Wheel::Init()
{
    m_textureWheelTable = Texture::CreateTexture("../src/resources/roulette/wheel/table_wheel.png");
    m_textureWheel = Texture::CreateTexture("../src/resources/roulette/wheel/wheel.png");
    m_textureWheelShadow = Texture::CreateTexture("../src/resources/roulette/wheel/wheel_shadow.png");

    if (!m_textureWheelTable->Load())
    {
        LOG_ERROR("Wheel - Unable to load texture table wheel !");
        return false;
    }

    if (!m_textureWheel->Load())
    {
        LOG_ERROR("Wheel - Unable to load texture wheel !");
        return false;
    }

    if (!m_textureWheelShadow->Load())
    {
        LOG_ERROR("Wheel - Unable to load texture wheel shadow !");
        return false;
    }

    LOG_INFO("Wheel - Initialized ...");
    return true;
}

bool Wheel::Deinit()
{
    LOG_WARN("Wheel - Deinitialized ...");
    return true;
}

void Wheel::Draw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    rend->DrawPicture(m_textureWheelTable, g_fXWheelTable, g_fYWheelTable);
    rend->SetColor(1.0f, 1.0f, 1.0f, 0.4f);
    rend->DrawPictureRotated(m_textureWheelShadow, g_fXWheelTable + g_fXWheelOffset - g_fXShadowOffset, g_fYWheelTable + g_fYWheelOffset - g_fYShadowOffset, m_fDegreesWheel);
    rend->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    rend->DrawPictureRotated(m_textureWheel, g_fXWheelTable + g_fXWheelOffset, g_fYWheelTable + g_fYWheelOffset, m_fDegreesWheel);
}

void Wheel::StartSlowRotation()
{
    m_eState = EWheelStates::eRotatingSlow;
    m_interpolatorAcceleration.Start(m_fSpeedWheel, 0.0f, GameDefs::g_fSlowSpeedWheel, Ease::SineIn, GameDefs::g_unAccelerationSlowSpeedDuration);
    MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerRotationWheel, g_unTimerRotationWheelPeriod);
    LOG_INFO("Wheel - Start Slow Rotation");
}

void Wheel::DecrementSlowRotationToZero()
{
    m_eState = EWheelStates::eDecrementingToZero;
    std::function<void()> endCallback = [this]()
    {
        StopRotation();
    };
    m_interpolatorDecceleration.SetEndCallback(endCallback);
    m_interpolatorDecceleration.Start(m_fSpeedWheel, GameDefs::g_fSlowSpeedWheel, 0.0f, Ease::SineIn, GameDefs::g_unDecelerationSlowSpeedDuration);
}

void Wheel::StopRotation()
{
    m_eState = EWheelStates::eStopped;
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unTimerRotationWheel);
    m_fSpeedWheel = 0.0f;
    if (m_wheelStoppedCallback)
    {
        m_wheelStoppedCallback();
    }
    LOG_INFO("Wheel - Stopped Rotation");
}

void Wheel::StartFastRotation()
{
    m_eState = EWheelStates::eRotatingFast;
    // m_interpolatorAcceleration.Start(m_fSpeedWheel, m_fSpeedWheel, g_fFastSpeedWheel, Ease::SineIn, g_unAccelerationSlowSpeedDuration);
    LOG_INFO("Wheel - Start Fast Rotation");
}

void Wheel::DecrementToSlowRotation()
{
    m_eState = EWheelStates::eRotatingSlow;
    // m_interpolatorAcceleration.Start(m_fSpeedWheel, g_fFastSpeedWheel, g_fSlowSpeedWheel, Ease::SineIn, g_unAccelerationDecrementSpeedDuration);
    LOG_INFO("Wheel - Decrement from Fast to Slow Rotation");
}

void Wheel::OnTick(unsigned int unID, unsigned int unTimes)
{
    if (unID == g_unTimerRotationWheel)
    {
        m_fDegreesWheel += m_fSpeedWheel;
        NormalizeAngle();

        /*Increment counter sector every time sector degrees change*/
        if (m_fDegreesWheel > (GameDefs::g_fAnglePerSector * m_unCounterSector))
        {
            ++m_unCounterSector;
        }
    }
}

void Wheel::SetWheelStoppedCallback(std::function<void()> &wheelStoppedCallback)
{
    m_wheelStoppedCallback = wheelStoppedCallback;
}

void Wheel::NormalizeAngle()
{
    if (m_fDegreesWheel >= 360.0f)
    {
        m_fDegreesWheel = 0.0f;
        m_unCounterSector = 0;
    }
}

const EWheelStates &Wheel::GetState()
{
    return m_eState;
}

const float &Wheel::GetSpeed()
{
    return m_fSpeedWheel;
}

const float &Wheel::GetDegrees()
{
    return m_fDegreesWheel;
}