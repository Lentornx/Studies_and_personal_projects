#include "UI.h"
#include "functions.h"

UI::UI()
{}

UI::~UI()
{}

void UI:: makeRect(SDL_Renderer* renderer, SDL_Surface* charset)
{
    destR.y = RECT_DEST_Y;
    destR.x = RECT_DEST_X;
    destR.h = RECT_SIZE_Y;
    destR.w = RECT_SIZE_X;

    infoDestR.y = INFO_RECT_DEST_Y;
    infoDestR.x = INFO_RECT_DEST_X;
    infoDestR.h = INFO_RECT_SIZE_Y;
    infoDestR.w = INFO_RECT_SIZE_X;

    screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH,
        RED_MASK, GREEN_MASK, BLUE_MASK, ALPHA_MASK);

    scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    black = SDL_MapRGB(screen->format, RGB_BLACK);
    red = SDL_MapRGB(screen->format, RGB_RED);

    SDL_SetColorKey(charset, true, KEY);
    scrtex = SDL_CreateTextureFromSurface(renderer, screen);
}

void UI::clean()
{
    SDL_DestroyTexture(scrtex);
    SDL_FreeSurface(screen);
}

void UI::gameOver(char *gameInfo, SDL_Surface* charset)
{
    SDL_FillRect(screen, &destR, black);
    DrawRectangle(screen, RECT_DEST_X + 1, RECT_DEST_Y + 1, RECT_SIZE_X - 1, RECT_SIZE_Y - 1, red, black);
    DrawString(screen, INPUT_INSTRUCTION_X, INPUT_INSTRUCTION_Y, GAME_OVER_MESSAGE, charset);
    DrawString(screen, INPUT_INSTRUCTION_X, INPUT_INSTRUCTION_Y + SPACE_BETWEEN_LINES, gameInfo , charset);    
    DrawString(screen, GAME_INFO_X, GAME_INFO_Y, GAME_OVER_INSTRUCTIONS, charset);
    SDL_UpdateTexture(scrtex, &destR, screen->pixels, screen->pitch);
}

void UI::update(SDL_Renderer* renderer, SDL_Surface* charset, char *gameInfo)
{
    SDL_FillRect(screen, &destR, black);
    DrawRectangle(screen, RECT_DEST_X+1, RECT_DEST_Y+1, RECT_SIZE_X-1, RECT_SIZE_Y-1, red, black);

    DrawString(screen, INPUT_INSTRUCTION_X, INPUT_INSTRUCTION_Y, INPUT_INSTRUCTION_1 , charset);
    DrawString(screen, INPUT_INSTRUCTION_X, INPUT_INSTRUCTION_Y + SPACE_BETWEEN_LINES, INPUT_INSTRUCTION_2, charset);

    DrawString(screen, GAME_INFO_X, GAME_INFO_Y, gameInfo, charset);
    
    SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);

}

void UI::render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, scrtex, NULL, NULL);
}
