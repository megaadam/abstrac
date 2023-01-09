// MIT License -- Copyright (c) 2023 Adam Horvath

#pragma once

#include "raylib.h"

#include <memory>
#include <random>
#include <vector>


class LayerCfg
{
public:

    // colour minmax (H)LS
    float minL = 0.6;
    float maxL = 1.0;
    float minS = 0.5;
    float maxS = 0.9;
};

class Layer
{
public:
    Layer(int w, int h, int fps, std::unique_ptr<LayerCfg> cfg = std::unique_ptr<LayerCfg> (new LayerCfg{}));
    Layer() = delete;

    Texture get(float time);

private:
    std::unique_ptr<LayerCfg> m_cfg;

    int m_width;
    int m_height;
};
