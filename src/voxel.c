#include "main_modules.h"

#ifndef INCL_VOXEL
    #define INCL_VOXEL
    #include "voxel.h"
#endif

Voxel* InitVoxel(Vector3 Position)
{
    Voxel* newV;
    newV = malloc(sizeof(Voxel));
    newV->Position = Position;

    // FACES PERPENDICULAR TO X
    newV->Faces[0].Position = (Vector3) { Position.x + 2.5, Position.y, Position.z};
    newV->Faces[1].Position = (Vector3) { Position.x - 2.5, Position.y, Position.z};
    
    newV->Faces[0].Size = (Vector3) { 0, 5, 5};
    newV->Faces[1].Size = (Vector3) { 0, 5, 5};

    // FACES PERPENDICULAR TO Y
    newV->Faces[2].Position = (Vector3) { Position.x, Position.y + 2.5, Position.z};
    newV->Faces[3].Position = (Vector3) { Position.x, Position.y - 2.5, Position.z};

    newV->Faces[2].Size = (Vector3) { 5, 0, 5};
    newV->Faces[3].Size = (Vector3) { 5, 0, 5};

    // FACES PERPENDICULAR TO Z
    newV->Faces[4].Position = (Vector3) { Position.x, Position.y, Position.z + 2.5};
    newV->Faces[5].Position = (Vector3) { Position.x, Position.y, Position.z - 2.5};

    newV->Faces[4].Size = (Vector3) { 5, 5, 0};
    newV->Faces[5].Size = (Vector3) { 5, 5, 0};
    
    for(int i = 0; i < 6; i++) newV->Faces[i].Visible = true;

    return newV;
}

void DrawVoxel(Voxel V,  Color color)
{
    for(int i = 0; i < 6; i++)
    {
        if(!V.Faces[i].Visible) continue;
        DrawCubeV(V.Faces[i].Position, V.Faces[i].Size, color);
    }
    DrawCubeWiresV(V.Position, (Vector3) { 5, 5, 5}, WHITE);
}

void DestroyVoxel(Voxel* V)
{
    free(V);
}

void CheckIfVisible(Voxel* V[16][16][16])
{
    for(int x = 0; x < 15; x++)
    {
        // CHECK Y Z = 16 TOP ROW
        if(V[x+1][15][15] != NULL)
        {
            V[x][15][15]->Faces[0].Visible = false;
            V[x+1][15][15]->Faces[1].Visible = false;
        }
        // CHECK EVERYTHING X Y Z < 15
        for(int z = 0; z < 15; z++)
        {
            for(int y = 0; y < 15; y++)
            {
                if(V[x+1][y][z] != NULL)
                {
                    V[x][y][z]->Faces[0].Visible = false;
                    V[x+1][y][z]->Faces[1].Visible = false;
                } 

                if(V[x][y+1][z] != NULL)
                {
                    V[x][y][z]->Faces[2].Visible = false;
                    V[x][y+1][z]->Faces[3].Visible = false;
                }

                if(V[x][y][z+1] != NULL)
                {
                    V[x][y][z]->Faces[4].Visible = false;
                    V[x][y][z+1]->Faces[5].Visible = false;
                }
            }

            // CHECK X Z SIDE 
            if(V[x+1][15][z] != NULL)
            {
                V[x][15][z]->Faces[0].Visible = false;
                V[x+1][15][z]->Faces[1].Visible = false;
            } 
            if(V[x][15][z+1] != NULL)
            {
                V[x][15][z]->Faces[4].Visible = false;
                V[x][15][z+1]->Faces[5].Visible = false;
            }
        }
    }

    // CHECK X Y SIDE
    for(int x = 0; x < 15; x++)
    {
        for(int y = 0; y < 15; y++)
        {
            if(V[x+1][y][15] != NULL)
            {
                V[x][y][15]->Faces[0].Visible = false;
                V[x+1][y][15]->Faces[1].Visible = false;
            } 

            if(V[x][y+1][15] != NULL)
            {
                V[x][y][15]->Faces[2].Visible = false;
                V[x][y+1][15]->Faces[3].Visible = false;
            }
        }
    }

    for(int y = 0; y < 15; y++)
    {
        // CHECK Y Z = 16 SIDE
        if(V[15][y+1][15] != NULL)
        {
            V[15][y][15]->Faces[2].Visible = false;
            V[15][y+1][15]->Faces[3].Visible = false;
        }
        for(int z = 0; z < 15; z++)
        {
            if(V[15][y+1][z] != NULL)
            {
                V[15][y][z]->Faces[2].Visible = false;
                V[15][y+1][z]->Faces[3].Visible = false;
            }

            if(V[15][y][z+1] != NULL)
            {
                V[15][y][z]->Faces[4].Visible = false;
                V[15][y][z+1]->Faces[5].Visible = false;
            }
        }
    }

    // CEHCK X Y = 16 ROW
    for(int z = 0; z < 15; z++)
    {
        if(V[15][15][z+1] != NULL)
        {
            V[15][15][z]->Faces[4].Visible = false;
            V[15][15][z+1]->Faces[5].Visible = false;
        }
    }
}

Chunk* GenerateChunk(Vector3 Offset)
{
    Chunk *newC = malloc(sizeof(Chunk));
    newC->Visible = true;
    newC->Offset = Offset;

    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                Vector3 pos =
                    { 
                        x*5 + newC->Offset.x*80, 
                        y*5 + newC->Offset.y*80, 
                        z*5 + newC->Offset.z*80,
                    };
                newC->Voxels[x][y][z] = InitVoxel(pos);
            }
        }
    }

    CheckIfVisible(newC->Voxels);
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