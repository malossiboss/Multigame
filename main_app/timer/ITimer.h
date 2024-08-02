#pragma once

#include <chrono>
#include <vector>

struct Timer
{
    unsigned int unID = 0;
    unsigned int unPeriod = 0;
    unsigned int unTimes = 0;
    bool bNeedToDeleteTimer = false;
    std::chrono::time_point<std::chrono::system_clock> startTime;
};

class ITimer
{

public:

    std::vector<Timer>m_vecTimers;
    virtual ~ITimer() { };
    virtual void OnTick(unsigned int unID, unsigned int unTimes) = 0;
};