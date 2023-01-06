// MIT License -- Copyright (c) 2023 Adam Horvath

#pragma once
#include "raylib.h"

#include <memory>
#include <random>
#include <vector>

class Star
{
public:
    Star(float _x, float _y, float _z, float rad, Color c, float f = 1.0)
    {
        x = _x;
        y = _y;
        z = _z;
        radius = rad;
        col = c;
        fade = f;
    }

    Star() = delete;

    float x;
    float y;
    float z;
    float radius;
    Color col;
    float fade;
};

class StarfallCfg {
public:
    float minLife = 1;
    float maxLife = 3.5;
    float minDepth = 33;
    float maxDepth = 444;
    float radius = 16.0;
    float hiatus = 12; // Average seconds without any starfall
    float fadeOut = 6.0 / 25; // time to die in s
};

class Starfall {
public:
    Starfall(std::unique_ptr<StarfallCfg> cfg);
    Starfall();

    Star* get(float time);

private:
    std::unique_ptr<StarfallCfg> m_cfg  = std::unique_ptr<StarfallCfg> (new StarfallCfg{});
    Star star = Star(0, 0, 0, m_cfg->radius, WHITE);
    Vector3 startPos;
    Vector3 endPos;
    float startTime;
    float endTime;
};

class StarfieldCfg
{
public:
    int count = 1888;
    float zSpeed = 40;  // screen units / s
    float rotSpeed = 3.0;  // degrees / s
    float minRadius = 4.0; // Radius in canvas pixels
    float maxRadius = 16.0;
    float camRatio = 1.0;
    float depthRatio = 8;

    float canvasRes = 2000; // a square canvas in pixels x pixels

    // Star colour minmax (H)LS
    float minL = 0.6;
    float maxL = 1.0;
    float minS = 0.5;
    float maxS = 0.9;
    float fadeIn = 4.0; // New stars fade in (s)
};

class Starfield
{
public:
    Starfield(int w, int h, int fps, std::unique_ptr<StarfieldCfg> cfg = std::unique_ptr<StarfieldCfg> (new StarfieldCfg{}));
    Starfield() = delete;

    Texture get(float time);

private:
    Star newStar(bool maxDepth = false, float fade = 1.0);

    Starfall m_starfall = Starfall();
    int m_width;
    int m_height;
    std::unique_ptr<StarfieldCfg> m_cfg;
    std::vector<Star> m_stars;

};
