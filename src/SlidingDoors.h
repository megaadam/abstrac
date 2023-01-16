// MIT License -- Copyright (c) 2023 Adam Horvath

#pragma once
#include "raylib.h"

#include <memory>
#include <random>
#include <vector>

#include "Anim.h"

class Door
{
public:
    Door(Anim<float>& _x, Anim<float>& _y, Anim<float>& _w, Anim<float>& _h, Color _col, float _ol);

    Anim<float> x;
    Anim<float> y;
    Anim<float> w;
    Anim<float> h;

    Color col;
    float ol; // outline width
    float speed;
};

class DoorsCfg
{
public:
    int count = 11;

    // Door colour minmax (H)LS
    float minL = 0.4;
    float maxL = 8.0;
    float minS = 0.8;
    float maxS = 1.0;
};

class SlidingDoors
{
public:
    SlidingDoors(int w, int h, int fps, std::unique_ptr<DoorsCfg> cfg = std::unique_ptr<DoorsCfg> (new DoorsCfg{}));
    SlidingDoors() = delete;

    Texture get(float time);

private:
    Door newDoor(float time);

    std::vector<Door> m_doors;
    std::unique_ptr<DoorsCfg> m_cfg;
    int m_width;
    int m_height;

};
