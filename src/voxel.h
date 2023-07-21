#ifndef INCL_RAYLIB
    #define INCL_RAYLIB
    #include "../include/raylib.h"
#endif

// Voxel
typedef struct
{
    bool Visible;
    Vector3 Position;
    Vector3 Size;
    Texture Texture;
}
VoxelFace;

typedef struct
{
    Vector3 Position;
    VoxelFace Faces[6];
} 
Voxel;

// Initializes Voxel
Voxel* InitVoxel(Vector3 Position);
// Draws Voxel of a desired color
void DrawVoxel(Voxel V, Color color);
// Deletes Voxel from memory
void DestroyVoxel(Voxel* V);
// Draws a Wireframe around the voxel when looking at it.
void Highlight(Voxel V);

// Chunk
typedef struct
{
    bool Visible;
    Vector3 Offset; // Offset compared to origin chunk
    Voxel* Voxels[16][16][16]; // 16 x 16 x 16 group of voxels
}
Chunk;

// Generates 16 x 16 x 16 solid block of voxels
Chunk* GenerateChunk(Vector3 Offset);
// Deletes chunk from memory.
void DestroyChunk(Chunk* C);
// Draws Chunk
void DrawChunk(Chunk C, Color color);
// Checks if voxels are visible, outermost voxels will always render
void CheckIfVisible(Voxel* V[16][16][16]); 