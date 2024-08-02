#pragma once

#include <random>

class Random
{

private:

public:

    static float GetRandomNumber(float fLowerBoundOpenInterval, float fUpperBoundClosedInterval)
    {
        std::uniform_real_distribution<> distribution(fLowerBoundOpenInterval, fUpperBoundClosedInterval);
        std::random_device rd;
        float fNumberToReturn  = distribution(rd);

        return fNumberToReturn;
    }


};