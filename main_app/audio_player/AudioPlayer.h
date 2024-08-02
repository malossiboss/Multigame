#pragma once

#include <string>
#include <irrKlang/include/irrKlang.h>
using namespace irrklang;

class AudioPlayer
{

private:

    /*Actual audio engine*/
    ISoundEngine* m_ptrSoundEngine = nullptr;

public:

    bool Init();
    bool Deinit();
    bool IsPlaying(const std::string& strFile);
    void PlaySound(const std::string& strFile, bool bLoop = false);
    void StopAllSounds();
    void SetVolume(float fVolume);

};