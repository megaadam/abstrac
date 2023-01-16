// MIT License -- Copyright (c) 2023 Adam Horvath

#include "SlidingDoors.h"

#include <algorithm>

#include "Anim.h"
#include "util.h"

SlidingDoors::SlidingDoors(int w, int h, int fps, std::unique_ptr<DoorsCfg> cfg)
{
    m_width = w;
    m_height = h;
    m_cfg = std::unique_ptr<DoorsCfg> (new DoorsCfg{});

    for (int i = 0; i < m_cfg->count; ++i)
    {
        auto door = newDoor(0);
        m_doors.push_back(door);
    }
}

Texture SlidingDoors::get(float time)
{
    static float lastTime = 0.0;
    float deltaTime = lastTime > 0 ? time - lastTime : 0.0;
    lastTime = time;

     RenderTexture2D canvas;
    canvas = LoadRenderTexture(m_width, m_height);
    // static RenderTexture2D cam = LoadRenderTexture(m_width, m_height); // animated camera

    BeginTextureMode(canvas);
        ClearBackground(WHITE);
        BeginBlendMode(BLEND_ALPHA);

        for(const auto& door: m_doors)
        {
            auto x = door.x.get(time);
            auto y = door.y.get(time);
            auto w = door.w.get(time);
            auto h = door.h.get(time);
            Rectangle rec{x - w / 2, y - h / 2, w, h };
            DrawRectanglePro(rec, Vector2{0, 0}, 0, door.col);
        }
        EndBlendMode();

        BeginBlendMode(BLEND_ADD_COLORS);
        for(auto& door: m_doors)
        {
            auto x = door.x.get(time);
            auto y = door.y.get(time);
            auto w = door.w.get(time);
            auto h = door.h.get(time);
            Rectangle rec{x - w / 2, y - h / 2, w, h };
            Color c2 = door.col;
            c2.a = 210;
            DrawRectangleLinesEx(rec, 4.0, c2);
            if (x + w / 2 < 0.0 || x - w / 2 > m_width)
            {
                door = newDoor(time);
            }
        }
        EndBlendMode();
    EndTextureMode();

    return canvas.texture;
}

Door SlidingDoors::newDoor(float time)
{
    static std::random_device dev;
    static std::default_random_engine eng(dev());
    static std::uniform_real_distribution<float> h_dist(0.1 * m_width, 0.9 * m_width);
    static std::uniform_real_distribution<float> v_dist(0.1 * m_height, 0.9 * m_height);
    static std::uniform_real_distribution<float> short_dist(0.1 * m_height, 0.2 * m_height);
    static std::uniform_real_distribution<float> long_dist(0.2 * m_height, 0.6 * m_height);;
    static std::uniform_real_distribution<float> time_dist(6, 10);


    float x = h_dist(eng);
    float y = v_dist(eng);
    float w = long_dist(eng);
    float h = short_dist(eng);

    Anim<float> xa;
    float t2 = time + time_dist(eng);
    if (x > m_width / 2)
    {
        xa = Anim<float>(time, t2, x, x - m_width);
    }
    else
    {
        xa = Anim<float>(time, t2, x, x + m_width);
    }

    Anim<float> ya(time, time, y, y);
    Anim<float> wa(time, time+2, 0, w);
    Anim<float> ha(time, time, h, h);


    Color col = rndHLS(0.0, 1.0, m_cfg->minL, m_cfg->maxL, m_cfg->minS, m_cfg->maxS, 144);

    Anim<float> a(1,2,3,4);
    return Door(xa, ya, wa, ha, col, 4);
}

Door::Door(Anim<float>& _x, Anim<float>& _y, Anim<float>& _w, Anim<float>& _h, Color _col, float _ol)
{
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    col = _col;
    ol = _ol;
}
