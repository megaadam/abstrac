// MIT License -- Copyright (c) 2023 Adam Horvath

#include "starfield.h"
#include "util.h"
Starfield::Starfield(int w, int h, int fps, std::unique_ptr<StarfieldCfg> cfg)
{
    m_width = w;
    m_height = h;
    m_cfg = std::unique_ptr<StarfieldCfg> (new StarfieldCfg{});

    m_stars.reserve(m_cfg->count);


    for (int i = 0; i < cfg->count; ++i)
    {
        Star star = newStar(false, 0.0);
        m_stars.push_back(star);
    }
}

Texture Starfield::get(float time)
{
    static float lastTime = 0.0;

    float deltaTime = lastTime > 0 ? time - lastTime : 0.0;
    lastTime = time;
    static RenderTexture2D target = LoadRenderTexture(m_width, m_height);
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    BeginTextureMode(target);
        ClearBackground(BLACK);

        for(auto& star: m_stars)
        {
            float x = (star.x * 100 / star.z + 100) * m_width / 200.0;
            float y = (star.y * 100 / star.z + 100) * m_height / 200.0;
            float rad = star.radius * 100 / star.z;

            Color starCol = star.col;
            if(star.fade < 1.0) {
                star.fade += deltaTime / m_cfg->fadeIn;
                starCol.a = int(star.fade * 255);
            }

            // DrawCircleV(Vector2{x, y}, rad, star.col);
            DrawCircleGradient(x, y, rad, starCol, Color{255, 255, 255, 0});

            star.z -= deltaTime * m_cfg->zSpeed;
            if (star.z < 10)
            {
                star = newStar(true, 0.0);
            }
        }
    EndTextureMode();

    return target.texture;
}

Star Starfield::newStar(bool maxDepth, float fade)
{
    static std::random_device dev;
    static std::default_random_engine eng(dev());
    static std::uniform_real_distribution<float> coord_dist(-100.0, 100.0);
    static std::uniform_real_distribution<float> depth_dist(100.0, 100.0 * m_cfg->depthRatio);
    static std::uniform_real_distribution<float> radius_dist(m_cfg->minRadius, m_cfg->maxRadius);

    float z =  maxDepth ? 100.0 * m_cfg->depthRatio : depth_dist(eng);
    float depthSqueze = maxDepth ? 1.9 : 1.0;
    Color col = rndHLS(0.0, 1.0, m_cfg->minL, m_cfg->maxL, m_cfg->minS, m_cfg->maxS);

    return Star(coord_dist(eng) * z / 100 / depthSqueze,
                coord_dist(eng) * z / 100 / depthSqueze, z, radius_dist(eng), col, fade);
}