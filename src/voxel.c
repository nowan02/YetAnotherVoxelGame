#include "main_modules.h"

#ifndef INCL_VOXEL
    #define INCL_VOXEL
    #include "voxel.h"
#endif

void DrawVoxel(Voxel V,  Color color)
{
    if(!V.Visible) return;  
    DrawCubeV(V.Position, (Vector3) { 5, 5, 5 }, color);
    DrawCubeWiresV(V.Position, (Vector3) { 5, 5, 5 }, WHITE);
}

void DestroyVoxel(Voxel* V)
{
    free(V);
}

void CheckIfVisible(Voxel* V[16][16][16])
{
    for(int x = 1; x < 15; x++)
    {
        for(int y = 1; y < 15; y++)
        {
            for(int z = 1; z < 15; z++)
            {
                if(V[x-1][y][z] != NULL && V[x][y-1][z] != NULL && V[x][y][z-1] != NULL)
                {
                    V[x][y][z]->Visible = false;
                }
            }
        }
    }
}

Chunk* GenerateChunk(Vector3 Offset)
{
    Chunk *newC = malloc(sizeof(bool) + sizeof(Vector3) + sizeof(Voxel* [16][16][16]));
    newC->Visible = true;
    newC->Offset = Offset;

    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                Voxel *newV;
                newV = malloc(sizeof(Voxel));
                newV->Position = (Vector3) 
                    { 
                        x*5 + newC->Offset.x*80, 
                        y*5 + newC->Offset.y*80, 
                        z*5 + newC->Offset.z*80,
                    };
                newV->Visible = true; // Later only visible will be drawn.

                newC->Voxels[x][y][z] = newV;
            }
        }
    }

    return newC;
}

void DrawChunk(Chunk C, Color color)
{
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                DrawVoxel(*C.Voxels[x][y][z], color);
            }
        }
    }
}

void DestroyChunk(Chunk* C)
{
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                DestroyVoxel(C->Voxels[x][y][z]);
            }
        }
    }

    free(C);
}