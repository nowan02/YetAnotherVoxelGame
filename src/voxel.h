#ifndef INCL_RAYLIB
    #define INCL_RAYLIB
    #include "../include/raylib.h"
#endif

// Voxel
typedef struct
{
    bool Visible;
    Vector3 Position;
    Model Plane;
}
VoxelFace;

typedef struct
{
    Vector3 Position;
    VoxelFace Faces[6];
    Material Materials[6];
    Texture2D Textures[6];
} 
Voxel;

// Initializes Voxel
Voxel* InitVoxel(Vector3 Position, Texture2D* VoxelTextures, Model Model);
// Draws Voxel of a desired color
void DrawVoxel(Voxel* V, Color color);
// Deletes Voxel from memory
void DestroyVoxel(Voxel* V);
// Breaks voxel
void BreakVoxel(Voxel* V);

// Chunk
typedef struct
{
    bool Visible;
    Vector3 Offset; // Offset compared to origin chunk
    Voxel* Voxels[16][16][16]; // 16 x 16 x 16 group of voxels
}
Chunk;

// Generates 16 x 16 x 16 solid block of voxels
Chunk* GenerateChunk(Vector3 Offset, Image* VoxelTextureMap);
// Deletes chunk from memory.
void DestroyChunk(Chunk* C);
// Draws Chunk
void DrawChunk(Chunk* C, Color color);
// Checks if voxels are visible, outermost voxels will always render
void Cull(Voxel* V[16][16][16]); 