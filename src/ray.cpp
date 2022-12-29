// MIT License -- Copyright (c) 2023 Adam Horvath

#include "ray.h"

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