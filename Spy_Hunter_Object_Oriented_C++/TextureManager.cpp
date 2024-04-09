#include "TextureManager.h"
#include "Defines.h"
SDL_Texture* TextureManager::LoadTexture(const char *texturePath, SDL_Renderer* renderer)
{
    SDL_Surface* tmpSurface = SDL_LoadBMP(texturePath);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return tex;
}