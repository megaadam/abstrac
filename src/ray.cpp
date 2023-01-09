// MIT License -- Copyright (c) 2023 Adam Horvath

#include "ray.h"

#include <math.h>

#include <stdio.h>

#include "starfield.h"
#include "SlidingDoors.h"

#include "util.h"

Texture2D getTex(int w, int h, int32_t col);
Texture2D getTex2(int w, int h);

int rayWin(int w, int h, int fps)
{
    InitWindow(defaultScreenWidth, defaultScreenHeight, "abstrac - first born baby");
    SetTargetFPS(fps);
    int tick = 0;
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("It begins...", 190, 200, 20, LIGHTGRAY);
            DrawText("keep on rollin", 400 -((tick) % 450) , 250 , 24, DARKPURPLE);
        EndDrawing();
        ++tick;
    }
    CloseWindow();
    return 0;
}

int rayWin2(int w, int h, int fps)
{
    const int screenWidth = w;
    const int screenHeight = h;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "abstrac - Test #2");

    Rectangle rec1 = { float(w)/4 - 80, float(h)/2, float(w)/1.7f, float(h)/2 };
    Rectangle rec2 = { float(w)/4*2 - 80, float(h)/2, float(w)/2, float(h)/4 };
    Rectangle rec3 = { float(w)/4*3 -80, float(h)/2, float(w)/1.7f, float(h)/2 };

    Vector2 origin = { float(w)/4, float(h)/4};
    Vector2 origin2 = { float(w)/4, float(h)/8};



    SetTargetFPS(fps);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        float rotation = 60.0f*GetTime();   // Rotate the rectangles, 60 degrees per second

        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            BeginBlendMode(BLEND_ADDITIVE);
            DrawRectanglePro(rec1, origin, rotation/2.0, DARKBLUE);
            DrawRectanglePro(rec2, origin2, rotation/2.0, DARKBROWN);
            DrawRectanglePro(rec3, origin, rotation/2.0, DARKPURPLE);
        EndDrawing();
    }
    return 0;
}

int rayWin3(int w, int h, int fps)
{
    const int screenWidth = w;
    const int screenHeight = h;

    const float count = 5.0;
    const float spacing = w / count;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "abstrac - Test #3");

    SetTargetFPS(fps);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
            ClearBackground(BLACK);
            BeginBlendMode(BLEND_ADDITIVE);
            for(int x=0; x < count; ++x) {
                for(int y=0; y < count -1; ++y) {
                    float xpos =(float)spacing/2 + x * spacing;
                    float ypos =(float)spacing/2 + y * spacing;

                    // DrawCircleV(Vector2{xpos, ypos}, spacing*0.6, rndHLS(0, 1, 0.3, 0.6, 0.6, 1.0));
                    Color c1 = rndHLS(0, 1, 0.3, 0.6, 0.6, 1.0);
                    Color c2 = c1;
                    c2.a = 0.0;
                    DrawCircleGradient(xpos, ypos, spacing*0.9, rndHLS(0, 1, 0.3, 0.6, 0.6, 0.8), c2);
                }
            }

        EndDrawing();

    }

    return 0;
}


int rayWin4(int w, int h, int fps)
{
    InitWindow(w, h, "abstrac - Test #4");

    SetTargetFPS(fps);
    Texture2D tex1 = getTex2(w, h);
    Texture2D tex2 = getTex2(w, h);

    int count = 0;
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        //BeginBlendMode(BLEND_ADDITIVE);

        if(++count % 2 == 0)
        {
            DrawTexture(tex1, 0, 0, WHITE);
        }
        else
        {
            DrawTexture(tex2, 0, 0, WHITE);
        }
        EndDrawing();
    }

    return 0;
}

int rayWin5(int w, int h, int fps, bool headless)
{
    SetTraceLogLevel(LOG_WARNING);

    if (headless == true)
    {
        SetConfigFlags(FLAG_WINDOW_HIDDEN | FLAG_MSAA_4X_HINT);
    }
    else
    {
        SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_MSAA_4X_HINT);
    }

    InitWindow(w, h, "abstrac - Starfield");
    int frame = 0;
    char buf[16] = {0};

    SetTargetFPS(fps);
    Starfield starfield(w, h, fps);
    SlidingDoors doors(w, h, fps);

    while (headless == true || WindowShouldClose() == false)
    {
        Texture tex = starfield.get(GetTime());

        if (true) // WIP
        {
            tex = doors.get(GetTime());
        }

        if(headless == false)
        {
            ClearBackground(BLACK);
            BeginDrawing();
            DrawTexture(tex, 0, 0, WHITE);
            EndDrawing();
        }
        else
        {
            sprintf(buf, "/mnt/ramdisk/starfield.%05i.png", (++frame)%2000);
            Image img = LoadImageFromTexture(tex);
            ExportImage(img, buf);
            UnloadImage(img);
        }
    }

    return 0;
}

Texture2D getTex(int w, int h, int32_t col) {
    int32_t* raw = (int32_t*)malloc(sizeof(int32_t) * w * h);
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            raw[y*w + x] = col;
        }
    }

    Image img{raw, w, h, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};

    ImageDrawCircleLinesV(&img, Vector2{w/2.0f, h*2.0f/3.0f}, h/4.0f, RAYWHITE);

    Texture2D tex = LoadTextureFromImage(img);
    UnloadImage(img);

    return tex;
}

Texture2D getTex2(int w, int h) {

    RenderTexture2D target = LoadRenderTexture(w, h);

    const float count = 5.0;
    const float spacing = w / count;
    BeginTextureMode(target);
        ClearBackground(BLACK);
        for(int x=0; x < count; ++x) {
            for(int y=0; y < count -1; ++y) {
                float xpos =(float)spacing/2 + x * spacing;
                float ypos =(float)spacing/2 + y * spacing;

                Color c1 = rndHLS(0, 1, 0.3, 0.6, 0.6, 1.0);
                Color c2 = c1;
                c2.a = 0.0f;
                DrawCircleGradient(xpos, ypos, spacing*0.9, rndHLS(0, 1, 0.3, 0.6, 0.6, 0.8), c2);
            }
        }
    EndTextureMode();

    return target.texture;
}

