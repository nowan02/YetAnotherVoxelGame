#include "main_modules.h"
#include "game_modules.h"

int main(void)
{
    InitWindow(800, 600, "Yet Another Voxel Game");
    SetTargetFPS(140);
    DisableCursor();

    Chunk* LoadedChunks[32];

    Chunk* newChunk = GenerateChunk((Vector3) { 0.0f, 0.0f, 0.0f });
    Chunk* newChunk2 = GenerateChunk((Vector3) { 1.0f, 0.0f, 0.0f });
    Chunk* newChunk3 = GenerateChunk((Vector3) { 0.0f, 0.0f, 1.0f });

    Camera3D PlayerCamera;
    PlayerCamera.fovy = 90;
    PlayerCamera.position = (Vector3) { 83.0f, 83.0f, 83.0f };
    PlayerCamera.target = (Vector3) { 0.0f, 0.0f, 0.0f };
    PlayerCamera.up = (Vector3) { 0.0f, 1.0f, 0.0f };
    PlayerCamera.projection = CAMERA_PERSPECTIVE;

    // Gameloop
    while(!WindowShouldClose())
    {
        CheckIfVisible(newChunk->Voxels);
        CheckIfVisible(newChunk2->Voxels);
        CheckIfVisible(newChunk3->Voxels);
        UpdateCamera(&PlayerCamera, CAMERA_FIRST_PERSON);
        BeginDrawing();
            DrawFPS(10, 10);
            ClearBackground(RAYWHITE);
            BeginMode3D(PlayerCamera);
            DrawChunk(*newChunk, RED);
            DrawChunk(*newChunk2, GREEN);
            DrawChunk(*newChunk3, BLUE);
            EndMode3D();
        EndDrawing();
    }

    DestroyChunk(newChunk);
    DestroyChunk(newChunk2);

    CloseWindow();

    return 0;
}