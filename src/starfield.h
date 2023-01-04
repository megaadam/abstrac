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

class StarfieldCfg {
    public:
        int count = 888;
        float zSpeed = 40;  // screen units / s
        float rotSpeed = 3.0;  // degrees / s
        float minRadius = 2.9; // Radius in canvas pixels
        float maxRadius = 11.0;
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
    int m_width;
    int m_height;
    std::unique_ptr<StarfieldCfg> m_cfg;
    std::vector<Star> m_stars;

};
