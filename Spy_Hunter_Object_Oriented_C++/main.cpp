#include<math.h>
#include<stdio.h>
#include<string.h>
#include "Defines.h"
#include "game.h"
#include "functions.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#ifdef __cplusplus
    extern "C"
#endif
 
int main(int argc, char** argv)
{
    Uint32 frameStart;
    int frameTime, frameDelay = FRAME_DELAY;
    Game* game;
    game = new Game();
    game->init(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT);
    while (game->running())
    {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        if (game->isGameOver())
            game->gameOver();
        game->render();
        if (game->restarted())
            game->restart();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }
    game->clean();
    return 0;
}
