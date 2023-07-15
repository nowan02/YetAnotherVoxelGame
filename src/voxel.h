#ifndef INCL_RAYLIB
    #define INCL_RAYLIB
    #include <raylib.h>
#endif

typedef struct
{
    bool Visible;
    Vector3 Position;
    Texture2D Faces[6];
} 
Voxel;

void DrawVoxel(Voxel V);
void Break(Voxel V);
void Highlight(Voxel V);