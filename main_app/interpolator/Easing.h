#pragma once

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

enum class Ease
{
    Linear,
    QuadraticIn,
    QuadraticOut,
    QuadraticInOut,
    CubicIn,
    CubicOut,
    CubicInOut,
    SineIn,
    SineOut,
    SineInOut,
    ExponentialIn,
    ExponentialOut,
    ExponentialInOut,
    CircularIn,
    CircularOut,
    CircularInOut,
    BounceIn,
    BounceOut,
    BounceInOut,
    ElasticIn,
    ElasticOut,
    ElasticInOut
};

namespace Easing
{
    template <typename T>
    static T LinearEasing(float position, T start, T end)
    {
        return static_cast<T>((end - start) * position + start);
    }

    template <typename T>
    static T QuadraticInEasing(float position, T start, T end)
    {
        return static_cast<T>((end - start) * position * position + start);
    }

    template <typename T>
    static T QuadraticOutEasing(float position, T start, T end)
    {
        return static_cast<T>((-(end - start)) * position * (position - 2) + start);
    }

    template <typename T>
    static T QuadraticInOutEasing(float position, T start, T end)
    {
        position *= 2;
        if (position < 1)
        {
            return static_cast<T>(((end - start) / 2) * position * position + start);
        }

        --position;
        return static_cast<T>((-(end - start) / 2) * (position * (position - 2) - 1) + start);
    }

    template <typename T>
    static T CubicInEasing(float position, T start, T end)
    {
        return static_cast<T>((end - start) * position * position * position + start);
    }

    template <typename T>
    static T CubicOutEasing(float position, T start, T end)
    {
        --position;
        return static_cast<T>((end - start) * (position * position * position + 1) + start);
    }

    template <typename T>
    static T CubicInOutEasing(float position, T start, T end)
    {
        position *= 2;
        if (position < 1)
        {
            return static_cast<T>(((end - start) / 2) * position * position * position + start);
        }
        position -= 2;
        return static_cast<T>(((end - start) / 2) * (position * position * position + 2) + start);
    }

    template <typename T>
    static T SineInEasing(float position, T start, T end)
    {
        return static_cast<T>(-(end - start) * cosf(position * static_cast<float>(M_PI) / 2) + (end - start) + start);
    }

    template <typename T>
    static T SineOutEasing(float position, T start, T end)
    {
        return static_cast<T>((end - start) * sinf(position * static_cast<float>(M_PI) / 2) + start);
    }

    template <typename T>
    static T SineInOutEasing(float position, T start, T end)
    {
        return static_cast<T>((-(end - start) / 2) * (cosf(position * static_cast<float>(M_PI)) - 1) + start);
    }

    template <typename T>
    static T ExponentialInEasing(float position, T start, T end)
    {
        return static_cast<T>((end - start) * powf(2, 10 * (position - 1)) + start);
    }

    template <typename T>
    static T ExponentialOutEasing(float position, T start, T end)
    {
        return static_cast<T>((end - start) * (-powf(2, -10 * position) + 1) + start);
    }

    template <typename T>
    static T ExponentialInOutEasing(float position, T start, T end)
    {
        position *= 2;
        if (position < 1)
        {
            return static_cast<T>(((end - start) / 2) * powf(2, 10 * (position - 1)) + start);
        }
        --position;
        return static_cast<T>(((end - start) / 2) * (-powf(2, -10 * position) + 2) + start);
    }

    template <typename T>
    static T CircularInEasing(float position, T start, T end)
    {
        return static_cast<T>(-(end - start) * (sqrtf(1 - position * position) - 1) + start);
    }

    template <typename T>
    static T CircularOutEasing(float position, T start, T end)
    {
        --position;
        return static_cast<T>((end - start) * (sqrtf(1 - position * position)) + start);
    }

    template <typename T>
    static T CircularInOutEasing(float position, T start, T end)
    {
        position *= 2;
        if (position < 1)
        {
            return static_cast<T>((-(end - start) / 2) * (sqrtf(1 - position * position) - 1) + start);
        }

        position -= 2;
        return static_cast<T>(((end - start) / 2) * (sqrtf(1 - position * position) + 1) + start);
    }

    template <typename T>
    static T BounceOutEasing(float position, T start, T end)
    {
        T c = end - start;
        if (position < (1 / 2.75f))
        {
            return static_cast<T>(c * (7.5625f * position * position) + start);
        }
        else if (position < (2.0f / 2.75f))
        {
            float postFix = position -= (1.5f / 2.75f);
            return static_cast<T>(c * (7.5625f * (postFix)*position + .75f) + start);
        }
        else if (position < (2.5f / 2.75f))
        {
            float postFix = position -= (2.25f / 2.75f);
            return static_cast<T>(c * (7.5625f * (postFix)*position + .9375f) + start);
        }
        else
        {
            float postFix = position -= (2.625f / 2.75f);
            return static_cast<T>(c * (7.5625f * (postFix)*position + .984375f) + start);
        }
    }
    
    template <typename T>
    static T BounceInEasing(float position, T start, T end)
    {
        return (end - start) - BounceOutEasing((1 - position), T(), (end - start)) + start;
    }

    template <typename T>
    static T BounceInOutEasing(float position, T start, T end)
    {
        if (position < 0.5f)
            return static_cast<T>(BounceInEasing(position * 2, T(), (end - start)) * .5f + start);
        else
            return static_cast<T>(BounceOutEasing((position * 2 - 1), T(), (end - start)) * .5f + (end - start) * .5f + start);
    }

    template <typename T>
    static T ElasticInEasing(float position, T start, T end)
    {
        if (position <= 0.00001f)
            return start;
        if (position >= 0.999f)
            return end;
        float p = .3f;
        auto a = end - start;
        float s = p / 4;
        float postFix =
            a * powf(2, 10 * (position -= 1)); // this is a fix, again, with post-increment operators
        return static_cast<T>(-(postFix * sinf((position - s) * (2 * static_cast<float>(M_PI)) / p)) + start);
    }

    template <typename T>
    static T ElasticOutEasing(float position, T start, T end)
    {
        if (position <= 0.00001f)
            return start;
        if (position >= 0.999f)
            return end;
        float p = .3f;
        auto a = end - start;
        float s = p / 4;
        return static_cast<T>(a * powf(2, -10 * position) * sinf((position - s) * (2 * static_cast<float>(M_PI)) / p) + end);
    }

    template <typename T>
    static T ElasticInOutEasing(float position, T start, T end)
    {
        if (position <= 0.00001f)
            return start;
        if (position >= 0.999f)
            return end;
        position *= 2;
        float p = (.3f * 1.5f);
        auto a = end - start;
        float s = p / 4;
        float postFix;

        if (position < 1)
        {
            postFix = a * powf(2, 10 * (position -= 1)); // postIncrement is evil
            return static_cast<T>(-0.5f * (postFix * sinf((position - s) * (2 * static_cast<float>(M_PI)) / p)) + start);
        }
        postFix = a * powf(2, -10 * (position -= 1)); // postIncrement is evil
        return static_cast<T>(postFix * sinf((position - s) * (2 * static_cast<float>(M_PI)) / p) * .5f + end);
    }
};