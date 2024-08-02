#include "AudioPlayer.h"

#include <debug/Logger.h>

bool AudioPlayer::Init()
{

    m_ptrSoundEngine = createIrrKlangDevice();

    if(!m_ptrSoundEngine)
    {
        LOG_ERROR("AudioPlayer - Unable to create sound engine !");
        return false;
    }

    return true;
}

bool AudioPlayer::Deinit()
{
    m_ptrSoundEngine->drop();

    LOG_WARN("AudioPlayer - Deinitialized ...");
    return true;
}

bool AudioPlayer::IsPlaying(const std::string& strFile)
{
    return m_ptrSoundEngine->isCurrentlyPlaying(strFile.c_str());
}

void AudioPlayer::PlaySound(const std::string& strFile, bool bLoop)
{
    m_ptrSoundEngine->play2D(strFile.c_str(), bLoop);
}

void AudioPlayer::StopAllSounds()
{
    m_ptrSoundEngine->stopAllSounds();
}

void AudioPlayer::SetVolume(float fVolume)
{
    m_ptrSoundEngine->setSoundVolume(fVolume);
}