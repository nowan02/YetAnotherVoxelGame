#ifndef INCL_RAYLIB
    #define INCL_RAYLIB
    #include <raylib.h>
#endif

#ifndef INCL_VOXEL
    #define INCL_VOXEL
    #include "voxel.h"
#endif

void DrawVoxel(Voxel V)
{
    if(!V.Visible) return;  
    DrawCubeV(V.Position, (Vector3) { 5, 5, 5 }, RED);
    DrawCubeWiresV(V.Position, (Vector3) { 5, 5, 5 }, WHITE);
}