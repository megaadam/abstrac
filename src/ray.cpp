// MIT License -- Copyright (c) 2023 Adam Horvath

#include "ray.h"

#include <math.h>

int rayWin(int w, int h, int fps)
{
    InitWindow(screenWidth, screenHeight, "abstrac - first born baby");
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
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = w;
    const int screenHeight = h;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "abstrac - Test #2");

    Rectangle rec1 = { float(w)/4 - 80, float(h)/2, float(w)/1.7, float(h)/2 };
    Rectangle rec2 = { float(w)/4*2 - 80, float(h)/2, float(w)/2, float(h)/4 };
    Rectangle rec3 = { float(w)/4*3 -80, float(h)/2, float(w)/1.7, float(h)/2 };

    Vector2 origin = { float(w)/4, float(h)/4};
    Vector2 origin2 = { float(w)/4, float(h)/8};



    SetTargetFPS(fps);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        float rotation = 60.0f*GetTime();   // Rotate the rectangles, 60 degrees per second

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------

        BeginDrawing();
            ClearBackground(BLACK);
            BeginBlendMode(BLEND_ADDITIVE);
            DrawRectanglePro(rec1, origin, rotation/2.0, DARKBLUE);
            DrawRectanglePro(rec2, origin2, rotation/2.0, DARKBROWN);
            DrawRectanglePro(rec3, origin, rotation/2.0, DARKPURPLE);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
}
