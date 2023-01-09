// MIT License -- Copyright (c) 2023 Adam Horvath

#pragma once
#include "raylib.h"

#include <memory>
#include <random>
#include <vector>

class Door
{
public:
    Door(float _x, float _y, float _w, float _h, Color _col, float _ol, float _s);

    float x;
    float y;
    float w;

    float h;
    Color col;
    float ol; // outline width
    float speed;

    void update(float time);

private:
    float scale = 0.0;
    float w_internal;
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
    Door newDoor();

    std::vector<Door> m_doors;
    std::unique_ptr<DoorsCfg> m_cfg;
    int m_width;
    int m_height;

};
