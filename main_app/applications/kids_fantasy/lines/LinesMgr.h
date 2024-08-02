#pragma once

#include <vector>

#include <main_app/timer/TimerMgr.h>
#include <main_app/particle_system/ParticleSystem.h>
#include <main_app/interpolator/Interpolator.h>
#include <main_app/applications/kids_fantasy/GameDefinitions.h>

class LinesMgr : public ITimer
{

private:

    /*Position head Lines*/
    float m_fXCurrentPosition = 0.0f;
    float m_fYCurrentPosition = 0.0f;

    /*Process current point*/
    unsigned int m_unIndexProcessPointAtPosition = 0;
    unsigned int m_unIndexCurrentWinElement = 0;

    /*Interpolators object*/
    Interpolator m_interpolatorX;
    Interpolator m_interpolatorY;

    /*Particle Effect Lines*/
    ParticleSystem m_particleLine;
    ParticleSystem m_particleHead;

    /*Texture Particle*/
    std::shared_ptr<Texture>m_textureParticle = nullptr;

    /*Container holding win lines in current game*/
    std::vector<unsigned int>m_vecPositions;

    /*Methods Begin - End streak*/
    void StartFirstPoint();
    void StartEndPoint();

    /*Method called every endstep to calculate next point*/
    void ProcessNextPoint();

public:

    bool Init();
    bool Deinit();
    void Draw();
    void OnTick(unsigned int unID, unsigned int unTimes) final;
    void Start(bool bStartTimer = true);
    void Stop();
};