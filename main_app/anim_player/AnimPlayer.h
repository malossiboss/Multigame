#pragma once

#include <string>
#include <vector>
#include <functional>

#include <main_app/texture/Texture.h>
#include <main_app/timer/TimerMgr.h>

enum class EAnimPlayerStates
{
    eInactive,
    ePlaying,
    ePaused,
    eTotalAnimPlayerStates
};

enum class EAnimPlayerPlayMode
{
    ePlayOnce,
    ePlayLooped,
    eTotalAnimPlayerPlayModes
};

class AnimPlayer : public ITimer
{

private:

    /*FPS*/
    float m_fFps = 0.0f;

    /*Current frame index of drawn animation*/
    unsigned int m_unCurrentFrameIndex = 0;

    /*Path to anim*/
    std::string m_strPath = "N/A";

    /*AnimPlayer state*/
    EAnimPlayerStates m_eState = EAnimPlayerStates::eInactive;

    /*AnimPlayer play mode*/
    EAnimPlayerPlayMode m_ePlayMode = EAnimPlayerPlayMode::ePlayLooped;

    /*Container holding all the images needed to play the animation*/
    std::vector<std::shared_ptr<Texture>>m_vecImages;

    /*Method called every change of frame*/
    std::function<void(unsigned int unCurrentFrame)>m_frameCallback;

    /*Method called in the end of the animation*/
    std::function<void()>m_endCallback;

public:

    bool Init(std::string strPathToAnim, float fFps);
    bool InitSurfaces(std::string strPathToAnim, float fFps);
    bool LoadTexturesFromSurfaces();
    bool Deinit();
    void Start(float fFps = 25.0f, EAnimPlayerPlayMode ePlayMode = EAnimPlayerPlayMode::ePlayLooped);
    void Stop();
    void Draw(float fX, float fY);
    void OnTick(unsigned int unID, unsigned int unTimes) final;
    void SetFrameCallback(std::function<void(unsigned int unCurrentFrame)>& frameCallback);
    void SetEndCallback(std::function<void()>& endCallback);
};