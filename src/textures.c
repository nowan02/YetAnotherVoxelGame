#include "main_modules.h"
#include <stdlib.h>

Texture2D* GetBlockTextures(Image* BlockTextures)
{
    Texture2D* tex = malloc(sizeof(Texture2D[6]));
    for(int i = 0; i < 6; i++)
    {
        tex[i] = LoadTextureFromImage(ImageFromImage(*BlockTextures, (Rectangle) { i*17, 0, 16, 16}));
    }
    return tex;
}