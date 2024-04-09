#pragma once
#include <stdio.h>
#include "Defines.h"

extern "C" {
#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"
}

#ifdef __cplusplus
extern "C"
#endif

class UI
{
public:
    UI();
    ~UI();

    void makeRect(SDL_Renderer* renderer, SDL_Surface* charset);

    void update(SDL_Renderer* renderer, SDL_Surface* charset, char* gameInfo);

    void render(SDL_Renderer* renderer);

    void gameOver(char* gameInfo, SDL_Surface* charset);

    void clean();

private:
    int black, red, blue, green;
    SDL_Surface* screen, * charset;
    SDL_Texture* scrtex;
    SDL_Rect destR, infoDestR;
};