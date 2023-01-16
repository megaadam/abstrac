// MIT License -- Copyright (c) 2023 Adam Horvath

#pragma once

#include "util.h"

template <class T> class Anim
{
public:
    Anim(float _startTime, float _endTime, T _v1, T _v2)
    {
        startTime = _startTime;
        endTime = _endTime;
        v1 = _v1;
        v2 = _v2;
    }

    Anim() {}

const T get(float time) const
{
    return interpol(time, startTime, endTime, v1, v2);
}

private:
    float startTime;
    float endTime;
    T v1;
    T v2;
};