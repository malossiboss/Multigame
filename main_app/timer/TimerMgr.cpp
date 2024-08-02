#include "TimerMgr.h"

#include <debug/Logger.h>

void TimerMgr::StartTimer(ITimer *client, unsigned int unID, unsigned int unPeriod)
{

    /*Check if there is already active timer*/
    for (auto &timer : client->m_vecTimers)
    {
        if (timer.unID == unID)
        {
            if (timer.bNeedToDeleteTimer)
            {
                timer.bNeedToDeleteTimer = false;
                timer.unTimes = 0;
                timer.unPeriod = unPeriod;
                // LOG_INFO("TimerMgr - Restarted timer with ID \"{0}\"", unID);
                return;
            }
            else
            {
                //LOG_CRITICAL("TimerMgr - Try to start already stated timer with ID \"{0}\"", unID);
                return;
            }
        }
    }

    /*Create current timer object*/
    Timer timerObj;
    timerObj.unID = unID;
    timerObj.unPeriod = unPeriod;
    timerObj.startTime = std::chrono::system_clock::now();

    /*Register current timer object in vector of timers in the current client*/
    client->m_vecTimers.emplace_back(timerObj);

    /*Register the current client in the vector of observer clients*/
    bool bRegisterClient = true;
    for (auto &clientElement : m_vecClients)
    {
        if (clientElement == client)
        {
            bRegisterClient = false;
            break;
        }
    }

    if (bRegisterClient)
    {
        m_vecClients.emplace_back(client);
    }

    // LOG_INFO("TimerMgr - StartTimer - Client - \"{0}\"", client);
    // LOG_INFO("TimerMgr - StartTimer - ID - \"{0}\"", unID);
    // LOG_INFO("TimerMgr - StartTimer - PERIOD - \"{0}\"", unPeriod);
}

void TimerMgr::StopTimer(ITimer *client, unsigned int unID)
{
    /*Mark timer for remove*/
    for (auto &elementClient : m_vecClients)
    {
        if (elementClient == client)
        {
            for (auto &timer : elementClient->m_vecTimers)
            {
                if (timer.unID == unID)
                {
                    timer.bNeedToDeleteTimer = true;
                    // LOG_INFO("TimerMgr - StopTimer - ID - \"{0}\"", unID);
                }
            }
        }
    }
}

void TimerMgr::EraseClient(ITimer *client)
{
    /*Iterate all clients*/
    for (auto it = m_vecClients.begin(); it != m_vecClients.end();)
    {
        /*If found, erase it*/
        if (*it == client)
        {
            //LOG_INFO("TimerMgr - Erased client from container clients - ID - \"{0}\"", client);
            it = m_vecClients.erase(it);
            break;
        }
        else
        {
            ++it;
        }
    }
}

void TimerMgr::Process()
{
    auto currentTime = std::chrono::system_clock::now();

    /*Iterate all clients*/
    for (auto &client : m_vecClients)
    {
        /*Check if there is any timer to remove from container*/
        for (auto it = client->m_vecTimers.begin(); it != client->m_vecTimers.end();)
        {
            if (it->bNeedToDeleteTimer)
            {
                // LOG_INFO("TimerMgr - Remove timer from container - ID - \"{0}\"", it->unID);
                it = client->m_vecTimers.erase(it);
            }
            else
            {
                ++it;
            }
        }

        /*Iterate all timers in current client*/
        for (auto &timer : client->m_vecTimers)
        {
            auto deltaTimeClient = currentTime - timer.startTime;
            auto deltaTimeClientInMillis = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTimeClient).count();

            /*Need to execute callback tick*/
            if (deltaTimeClientInMillis >= timer.unPeriod)
            {
                timer.startTime = currentTime;
                client->OnTick(timer.unID, ++timer.unTimes);
            }
        }
    }
}