#include "main_modules.h"
#include "game_modules.h"
#include <raylib.h>

void Init(void)
{
    InitWindow(800, 600, "Yet Another Voxel Game");
    SetTargetFPS(140);
    DisableCursor();
}

int main(void)
{
    Init();

    Chunk* newChunk = GenerateChunk((Vector3) { 0.0f, 0.0f, 0.0f });
    Chunk* newChunk2 = GenerateChunk((Vector3) { 1.0f, 0.0f, 0.0f });

    Camera3D PlayerCamera;
    PlayerCamera.fovy = 90;
    PlayerCamera.position = (Vector3) { 100.0f, 100.0f, 100.0f };
    PlayerCamera.target = (Vector3) { 0.0f, 0.0f, 0.0f };
    PlayerCamera.up = (Vector3) { 0.0f, 1.0f, 0.0f };
    PlayerCamera.projection = CAMERA_PERSPECTIVE;

    // Gameloop
    while(!WindowShouldClose())
    {
        UpdateCamera(&PlayerCamera, CAMERA_FIRST_PERSON);
        BeginDrawing();
            DrawFPS(10, 10);
            ClearBackground(RAYWHITE);
            BeginMode3D(PlayerCamera);
            DrawChunk(*newChunk);
            DrawChunk(*newChunk2);
            EndMode3D();
        EndDrawing();
    }

    DestroyChunk(newChunk);
    DestroyChunk(newChunk2);

    CloseWindow();

    return 0;
}