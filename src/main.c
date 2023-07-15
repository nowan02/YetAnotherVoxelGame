#include "main_modules.h"

void Init(void)
{
    InitWindow(800, 600, "Yet Another Voxel Game");
    SetTargetFPS(140);
    DisableCursor();
}

int main(void)
{
    Init();

    Voxel newV;
    newV.Position = (Vector3) { 10, 10, 10 };
    newV.Visible = true;

    Camera3D PlayerCamera;
    PlayerCamera.fovy = 90;
    PlayerCamera.position = (Vector3) { 10.0f, 10.0f, 10.0f };
    PlayerCamera.target = (Vector3) { 0.0f, 0.0f, 0.0f };
    PlayerCamera.up = (Vector3) { 0.0f, 1.0f, 0.0f };
    PlayerCamera.projection = CAMERA_PERSPECTIVE;

    // Gameloop
    while(!WindowShouldClose())
    {
        UpdateCamera(&PlayerCamera, CAMERA_FIRST_PERSON);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(PlayerCamera);
            DrawVoxel(newV);
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}