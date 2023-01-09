// MIT License -- Copyright (c) 2023 Adam Horvath

#include "Layer.h"
#include "util.h"

Layer::Layer(int w, int h, int fps, std::unique_ptr<LayerCfg> cfg)
{
    m_width = w;
    m_height = h;
    m_cfg = std::unique_ptr<LayerCfg> (new LayerCfg{});


}

Texture Layer::get(float time)
{
    static float lastTime = 0.0;
    float deltaTime = lastTime > 0 ? time - lastTime : 0.0;
    lastTime = time;

    static RenderTexture2D canvas = LoadRenderTexture(m_width, m_height);
    // static RenderTexture2D cam = LoadRenderTexture(m_width, m_height); // animated camera

    BeginTextureMode(canvas);
        ClearBackground(RAYWHITE);
    EndTextureMode();

    // // animated camera
    // BeginTextureMode(cam);
    //     float canvasScale = res / sqrt(m_width * m_width + m_height * m_height);
    //     float xorig = res / 2 - m_width * canvasScale / 2;
    //     float yorig = res / 2 - m_height * canvasScale / 2;
    //     Rectangle canvasRect{xorig, yorig, m_width * canvasScale, m_height * canvasScale};
    //     Rectangle camRect{(float)m_width/2, (float)m_height/2, (float)m_width * 2, (float)m_height * 2};
    //     DrawTexturePro(canvas.texture, canvasRect, camRect, Vector2{m_width, m_height}, rot, Color{255, 255, 255, 255});
    // EndTextureMode();
    // rot += deltaTime * m_cfg->rotSpeed;

    return canvas.texture;
}
