#include "main_modules.h"
#include "game_modules.h"

Voxel* InitVoxel(Vector3 Position, Texture2D* VoxelTextures, Model Model)
{
    Voxel* newV;
    newV = malloc(sizeof(Voxel));
    newV->Position = Position;

    // FACES PERPENDICULAR TO X
    newV->Faces[0].Position = (Vector3) { Position.x + 2.5, Position.y, Position.z};
    newV->Faces[1].Position = (Vector3) { Position.x - 2.5, Position.y, Position.z};

    newV->Faces[0].Plane = Model;
    newV->Faces[1].Plane = Model;

    // FACES PERPENDICULAR TO Y
    newV->Faces[2].Position = (Vector3) { Position.x, Position.y + 2.5, Position.z};
    newV->Faces[3].Position = (Vector3) { Position.x, Position.y - 2.5, Position.z};

    newV->Faces[2].Plane = Model;
    newV->Faces[3].Plane = Model;

    // FACES PERPENDICULAR TO Z
    newV->Faces[4].Position = (Vector3) { Position.x, Position.y, Position.z + 2.5};
    newV->Faces[5].Position = (Vector3) { Position.x, Position.y, Position.z - 2.5};

    newV->Faces[4].Plane = Model;
    newV->Faces[5].Plane = Model;

    for(int i = 0; i < 6; i++)
    {
        newV->Faces[i].Visible = true;
    }

    return newV;
}

void DrawVoxel(Voxel* V,  Color color)
{
    // DRAW FACES PERPENDICULAR TO X
    if(V->Faces[0].Visible) DrawModelEx(V->Faces[0].Plane, V->Faces[0].Position, (Vector3) { 0, 0, 1 }, -90.0f, (Vector3) { 1, 1, 1 }, BLUE);
    if(V->Faces[1].Visible) DrawModelEx(V->Faces[1].Plane, V->Faces[1].Position, (Vector3) { 0, 0, 1 }, 90.0f, (Vector3) { 1, 1, 1 }, BLUE);

    // DRAW FACES PERPENDICULAR TO Y
    if(V->Faces[2].Visible) DrawModelEx(V->Faces[2].Plane, V->Faces[2].Position, (Vector3) { 0, 0, 0 }, 0, (Vector3) { 1, 1, 1 }, RED);
    if(V->Faces[3].Visible) DrawModelEx(V->Faces[3].Plane, V->Faces[3].Position, (Vector3) { 0, 0, 1 }, 180.0f, (Vector3) { 1, 1, 1 }, RED);

    // DRAW FACES PERPENDICULAR TO Z
    if(V->Faces[4].Visible) DrawModelEx(V->Faces[4].Plane, V->Faces[4].Position, (Vector3) { 1, 0, 0 }, 90.0f, (Vector3) { 1, 1, 1 }, GREEN);
    if(V->Faces[5].Visible) DrawModelEx(V->Faces[5].Plane, V->Faces[5].Position, (Vector3) { 1, 0, 0 }, -90.0f, (Vector3) { 1, 1, 1 }, GREEN);
}

void DestroyVoxel(Voxel* V)
{
    free(V);
}

void Cull(Voxel* V[16][16][16])
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

Chunk* GenerateChunk(Vector3 Offset, Image* VoxelTextureMap)
{
    Chunk *newC = malloc(sizeof(Chunk));
    newC->Visible = true;
    newC->Offset = Offset;

    // SEPARATE!!!!
    Model Plane = LoadModelFromMesh(GenMeshPlane(5.0f, 5.0f, 16, 16));
    Texture2D* T = GetVoxelTexture(VoxelTextureMap);

    Plane.materialCount = 6;
    Plane.materials = malloc(sizeof(Material[6]));
    for(int i = 0; i < 6; i++)
    {
        Plane.materials[i] = LoadMaterialDefault();
        SetMaterialTexture(&Plane.materials[i], MATERIAL_MAP_DIFFUSE, T[i]);
        SetModelMeshMaterial(&Plane, 0, i);
    } 
    // SEPARATE!!!

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
                newC->Voxels[x][y][z] = InitVoxel(pos, T, Plane);
            }
        }
    }

    Cull(newC->Voxels);
    return newC;
}

void DrawChunk(Chunk* C, Color color)
{
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                DrawVoxel(C->Voxels[x][y][z], color);
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