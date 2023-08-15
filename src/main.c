#include "main_modules.h"
#include "game_modules.h"

int main(void)
{
    Image Voxels = LoadImage("textures/blocks.png");

    InitWindow(800, 600, "Yet Another Voxel Game");
    SetTargetFPS(140);
    DisableCursor();

    Chunk* Test = GenerateChunk((Vector3) {0,0,0}, &Voxels);

    Camera3D PlayerCamera;
    PlayerCamera.fovy = 90;
    PlayerCamera.position = (Vector3) { 0.0f, 80.0f, 2.0f };
    PlayerCamera.target = (Vector3) { 0.0f, 0.0f, 0.0f };
    PlayerCamera.up = (Vector3) { 0.0f, 1.0f, 0.0f };
    PlayerCamera.projection = CAMERA_PERSPECTIVE;

    // Gameloop
    while(!WindowShouldClose())
    {
        UpdateCamera(&PlayerCamera, CAMERA_FIRST_PERSON);
        BeginDrawing();
            DrawFPS(10, 10);
            ClearBackground(BLACK);
            BeginMode3D(PlayerCamera);
            DrawChunk(Test, BLUE);
            EndMode3D();
        EndDrawing();
    }

    DestroyChunk(Test);

    CloseWindow();

    return 0;
}