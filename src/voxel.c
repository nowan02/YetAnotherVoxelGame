#include "main_modules.h"
#include <raylib.h>

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

void DestroyVoxel(Voxel* V)
{
    free(V);
}

Chunk* GenerateChunk(Vector3 Offset)
{
    Chunk *newC = malloc(sizeof(bool) + sizeof(Vector3) + sizeof(Voxel* [4096]));
    newC->Visible = true;
    newC->Offset = Offset;

    int i, x, y, z;
    i = 0;

    for(x = 0; x < 16; x++)
    {
        for(y = 0; y < 16; y++)
        {
            for(z = 0; z < 16; z++)
            {
                Voxel *newV;
                newV = malloc(sizeof(Voxel));
                newV->Position = (Vector3) 
                    { 
                        x*5 + (int)newC->Offset.x*64, 
                        y*5 + (int)newC->Offset.y*64, 
                        z*5 + (int)newC->Offset.z*64
                    };
                newV->Visible = true; // Later only visible will be drawn.

                newC->Voxels[i] = newV;
                i++;
            }
        }
    }

    return newC;
}

void DrawChunk(Chunk C)
{
    for(int i = 0; i < 4096; i++)
    {
        DrawVoxel(*C.Voxels[i]);
    }
}

void DestroyChunk(Chunk* C)
{
    for(int i = 0; i < 4096; i++)
    {
        DestroyVoxel(C->Voxels[i]);
    }

    free(C);
}