#pragma once

#include <string>
#include <map>
#include <vector>

#include <main_app/applications/IApp.h>
#include <main_app/texture/Texture.h>
#include <main_app/timer/TimerMgr.h>
#include <main_app/particle_system/ParticleSystem.h>


class ParticleBuilder : public IApp, public ITimer
{

private:
    std::string m_strAppName = "Particle_Builder";

    /*Main Menu flag*/
    bool m_bMainMenuFlag = true;

    /*Create new particle flag modal popup*/
    bool m_bCreateNewParticle = false;

    /*Delete existing particle flag modal popup*/
    bool m_bDeleteExistingParticle = false;

    /*Max buff count*/
    const unsigned int m_unTextBuff = 64;

    /*Particle to be deleted*/
    std::string m_strIDParticleToBeDeleted  = "N/A";

    /*Container holding created particles*/
    std::map<std::string, ParticleSystem>m_mapParticles;

    /*Textures Particles*/
    std::vector<std::shared_ptr<Texture>>m_vecTexturesParticle;

    /*Method draws main menu*/
    void DrawMainMenu();

    /*Drawing collapsing list of particles*/
    void DrawActiveListParticles();

public:
    ParticleBuilder();

    bool Init() override;
    bool Deinit() override;
    bool HandleEvent() override;
    const std::string &GetAppName() override;
    void OnEnter() override;
    void OnExit() override;
    void OnDraw() override;
    void OnTick(unsigned int unID, unsigned int unTimes) final;
};