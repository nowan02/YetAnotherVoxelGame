#ifndef INCL_RAYLIB
    #define INCL_RAYLIB
    #include <raylib.h>
#endif

// Voxels
typedef struct
{
    bool Visible;
    Vector3 Position;
    Texture2D Faces[6];
} 
Voxel;


void DrawVoxel(Voxel V);
void DestroyVoxel(Voxel* V);
void Highlight(Voxel V);

// Chunks
typedef struct
{
    bool Visible;
    Vector3 Offset; // Offset compared to origin chunk
    Voxel* Voxels[4096]; // 16 x 16 x 16 group of voxels
}
Chunk;

Chunk* GenerateChunk(Vector3 Offset);
void DestroyChunk(Chunk* C);
void DrawChunk(Chunk C);
