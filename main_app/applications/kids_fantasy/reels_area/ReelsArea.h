#pragma once

#include <functional>

#include <main_app/anim_player/AnimPlayer.h>
#include <main_app/texture/Texture.h>
#include <main_app/timer/TimerMgr.h>
#include <main_app/applications/kids_fantasy/GameDefinitions.h>
#include <main_app/applications/kids_fantasy/reels_area/reels/Reel.h>

class ReelsArea : public ITimer
{

private:
    /*Texture Reels Area*/
    std::shared_ptr<Texture> m_textureReelsArea;

    /*Texture Hearth*/
    std::shared_ptr<Texture> m_textureHearth;

    /*Container with reels*/
    std::array<Reel, GameDefs::eTotalReelCount> m_arrReels;

    /*Container with figure textures*/
    std::array<std::shared_ptr<Texture>, GameDefs::eTotalGameFiguresCount> m_arrFiguresTexture;

    /*Container with figure animations*/
    std::array<AnimPlayer, GameDefs::eTotalGameFiguresCount> m_arrFiguresAnimations;

    /*Method called after all reels stopped*/
    std::function<void()> m_afterReelingStoppedCallback;
    
    /*Method starting all animations if there is a win*/
    void StartAnimationsIfAny();
    
public:
    bool Init();
    bool Deinit();
    bool HandleEvent();
    void Draw();
    void OnTick(unsigned int unID, unsigned int unTimes) final;

    /*After reeling stopped, will be executed m_afterReelingStoppedCallback*/
    void SetAfterReelingStoppedCallback(std::function<void()> &afterReelingStoppedCallback);

    /*Start new game method, when ENTER pressed will be executed*/
    bool StartNewGame(bool bDemoMode = false);

    /*Method called in different thread, due to time saving*/
    void LoadAnimationSurfaces();

    /*Method called after LoadAnimationSurfaces() in MAIN THREAD !*/
    void LoadTexturesFromSurfaces();

    /*Method called when exit from game, unloads needed resources*/
    void UnloadResources();
};