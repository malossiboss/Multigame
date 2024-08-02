#include "AnimPlayer.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <debug/Logger.h>

constexpr unsigned int g_unTimerProcessAnimPlayer = 1;

bool AnimPlayer::Init(std::string strPathToAnim, float fFps)
{
    /*Check if container already full*/
    if (!m_vecImages.empty())
    {
        LOG_ERROR("Anim Player - \"{0}\" already initialized !", strPathToAnim);

        return false;
    }

    /*Create filesystem (C++17) and extension search*/
    namespace fs = std::filesystem;
    using iterator = fs::recursive_directory_iterator;
    const std::string strExtention = ".png";

    /*Search in the directory for files, insert in set container due to alphabetical order*/
    std::set<std::string> containerFilesPath;
    if (fs::is_directory(strPathToAnim))
    {
        for (const auto &file : fs::recursive_directory_iterator(strPathToAnim))
        {
            if (file.is_regular_file() && file.path().extension() == strExtention)
            {
                containerFilesPath.insert(file.path().string());
            }
        }
    }

    /*Load all images from current path folder*/
    for (const auto &files : containerFilesPath)
    {
        std::shared_ptr<Texture> textureToInsert = Texture::CreateTexture(files);

        if (!textureToInsert->Load())
        {
            LOG_ERROR("Anim Player - Unable to load texture \"{0}\"", textureToInsert->GetPath());

            return false;
        }

        m_vecImages.emplace_back(textureToInsert);
    }

    m_fFps = fFps;
    m_unCurrentFrameIndex = 0;
    m_strPath = strPathToAnim;
    m_eState = EAnimPlayerStates::eInactive;
    m_ePlayMode = EAnimPlayerPlayMode::ePlayLooped;

    LOG_INFO("AnimPlayer - Initialized player with path: \"{0}\"", m_strPath);

    return true;
}

bool AnimPlayer::InitSurfaces(std::string strPathToAnim, float fFps)
{
    /*Check if container already full*/
    if (!m_vecImages.empty())
    {
        LOG_ERROR("Anim Player - \"{0}\" already initialized surfaces!", strPathToAnim);

        return false;
    }

    /*Create filesystem (C++17) and extension search*/
    namespace fs = std::filesystem;
    using iterator = fs::recursive_directory_iterator;
    const std::string strExtention = ".png";

    /*Search in the directory for files, insert in set container due to alphabetical order*/
    std::set<std::string> containerFilesPath;
    if (fs::is_directory(strPathToAnim))
    {
        for (const auto &file : fs::recursive_directory_iterator(strPathToAnim))
        {
            if (file.is_regular_file() && file.path().extension() == strExtention)
            {
                containerFilesPath.insert(file.path().string());
            }
        }
    }

    /*Load all images from current path folder*/
    for (const auto &files : containerFilesPath)
    {
        std::shared_ptr<Texture> textureToInsert = Texture::CreateTexture(files);

        if (!textureToInsert->LoadSurface())
        {
            LOG_ERROR("Anim Player - Unable to create surfce \"{0}\"", textureToInsert->GetPath());

            return false;
        }

        m_vecImages.emplace_back(textureToInsert);
    }

    m_fFps = fFps;
    m_unCurrentFrameIndex = 0;
    m_strPath = strPathToAnim;
    m_eState = EAnimPlayerStates::eInactive;
    m_ePlayMode = EAnimPlayerPlayMode::ePlayLooped;

    LOG_INFO("AnimPlayer - Initialized surfaces player with path: \"{0}\"", m_strPath);

    return true;
}

bool AnimPlayer::LoadTexturesFromSurfaces()
{
    for(auto& image : m_vecImages)
    {
        if(!image->LoadTextureFromSurface())
        {
            return false;
        }
    }

    return true;
}

bool AnimPlayer::Deinit()
{
    if(m_vecImages.empty())
    {
        return true;
    }

    Stop();

    for (auto &texture : m_vecImages)
    {
        texture->DeleteTexture();
    }

    m_vecImages.clear();

    LOG_WARN("AnimPlayer - Deinitialized player with path: \"{0}\"", m_strPath);
    m_strPath = "N/A";

    return true;
}

void AnimPlayer::Start(float fFps, EAnimPlayerPlayMode ePlayMode)
{
    if (m_vecImages.empty())
    {
        LOG_ERROR("Anim Player - AnimPlayer has to be initialized first!");

        return;
    }

    if (m_eState == EAnimPlayerStates::ePlaying)
    {
        return;
    }

    m_eState = EAnimPlayerStates::ePlaying;
    m_ePlayMode = ePlayMode;
    m_unCurrentFrameIndex = 0;
    const unsigned int unPeriodToStartTimerProcess = 1000 / fFps;
    MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerProcessAnimPlayer, unPeriodToStartTimerProcess);
}

void AnimPlayer::Stop()
{
    m_eState = EAnimPlayerStates::eInactive;
    m_unCurrentFrameIndex = 0;
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unTimerProcessAnimPlayer);
}

void AnimPlayer::Draw(float fX, float fY)
{
    if (m_eState == EAnimPlayerStates::eInactive)
    {
        return;
    }

    const auto &rend = MainApp::GetInstance().ptrRend;
    rend->DrawPicture(m_vecImages[m_unCurrentFrameIndex], fX, fY);
}

void AnimPlayer::OnTick(unsigned int unID, unsigned int unTimes)
{
    if (unID == g_unTimerProcessAnimPlayer)
    {
        /*Call frame callback evey change of frame*/
        if (m_frameCallback && m_eState == EAnimPlayerStates::ePlaying)
        {
            m_frameCallback(m_unCurrentFrameIndex + 1);
        }

        if (++m_unCurrentFrameIndex >= m_vecImages.size())
        {
            m_unCurrentFrameIndex = 0;

            switch (m_ePlayMode)
            {

            case EAnimPlayerPlayMode::ePlayOnce:
            {
                /*Call end callback in the end of the cycle, and stop*/
                if (m_endCallback)
                {
                    m_endCallback();
                }

                m_eState = EAnimPlayerStates::eInactive;
                MainApp::GetInstance().ptrTimer->StopTimer(this, g_unTimerProcessAnimPlayer);
            }
            break;

            case EAnimPlayerPlayMode::ePlayLooped:
            {
                /*Call end callback in the end of the cycle*/
                if (m_endCallback)
                {
                    m_endCallback();
                }
            }
            break;

            default:
                break;
            }
        }
    }
}

void AnimPlayer::SetFrameCallback(std::function<void(unsigned int unCurrentFrame)> &frameCallback)
{
    m_frameCallback = frameCallback;
}

void AnimPlayer::SetEndCallback(std::function<void()> &endCallback)
{
    m_endCallback = endCallback;
}