// MIT License -- Copyright (c) 2023 Adam Horvath

#include "SlidingDoors.h"

#include <algorithm>

#include "util.h"

SlidingDoors::SlidingDoors(int w, int h, int fps, std::unique_ptr<DoorsCfg> cfg)
{
    m_width = w;
    m_height = h;
    m_cfg = std::unique_ptr<DoorsCfg> (new DoorsCfg{});

    for (int i = 0; i < m_cfg->count; ++i)
    {
        m_doors.push_back(newDoor());
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
            Rectangle rec{door.x - door.w / 2, door.y - door.h / 2, door.w, door.h };
            DrawRectanglePro(rec, Vector2{0, 0}, 0, door.col);
        }
        EndBlendMode();

        BeginBlendMode(BLEND_ADD_COLORS);
        for(auto& door: m_doors)
        {
            Rectangle rec{door.x - door.w / 2, door.y - door.h / 2, door.w, door.h };
            Color c2 = door.col;
            c2.a = 210;
            DrawRectangleLinesEx(rec, 4.0, c2);
            door.update(deltaTime);
            if (door.x + door.w / 2 < 0.0 || door.x - door.w / 2 > m_width)
            {
                door = newDoor();
            }
        }
        EndBlendMode();
    EndTextureMode();

    return canvas.texture;
}

Door SlidingDoors::newDoor()
{
    static std::random_device dev;
    static std::default_random_engine eng(dev());
    static std::uniform_real_distribution<float> h_dist(0.1 * m_width, 0.9 * m_width);
    static std::uniform_real_distribution<float> v_dist(0.1 * m_height, 0.9 * m_height);
    static std::uniform_real_distribution<float> short_dist(0.1 * m_height, 0.2 * m_height);
    static std::uniform_real_distribution<float> long_dist(0.2 * m_height, 0.6 * m_height);;
    static std::uniform_real_distribution<float> speed_dist(m_width / 20, m_width / 8);;


    float x = h_dist(eng);
    float y = v_dist(eng);
    float w = long_dist(eng);
    float h = short_dist(eng);
    float speed = speed_dist(eng);
    if (x > m_width / 2)
    {
        speed = -speed;
    }

    Color col = rndHLS(0.0, 1.0, m_cfg->minL, m_cfg->maxL, m_cfg->minS, m_cfg->maxS, 144);

    return {x, y, w, h, col, 1.0f, speed};

}

Door::Door(float _x, float _y, float _w, float _h, Color _col, float _ol, float _s)
{
    x = _x;
    y = _y;
    w = 0.0;
    w_internal = _w;
    h = _h;
    col = _col;
    ol = _ol;
    speed = _s;
}


void Door::update(float deltaTime)
{
    x += deltaTime * speed;
    scale = std::min(scale + deltaTime* 0.33f, 1.0f);
    w = w_internal * scale;
}