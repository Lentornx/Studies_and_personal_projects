#pragma once
#include <stdio.h>
#include "Defines.h"
#include "Laser.h"

extern "C" {
#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"
}

#ifdef __cplusplus
extern "C"
#endif

class Map
{
public:

    Map();
    ~Map();

    void roadInfo(int* roadStart, int* roadWidth, int* roadStartRear, int* roadWidthFrontRear); // gives info of current line
    void generateRoadBorders(int* roadStart, int* roadWidth); // generates road width and starting point for the new map line
    void init(SDL_Renderer* renderer);
    void move(); //moves all the tiles in the layout arr one unit down, and generates a new line
    void update(int speed); // checks if there is enough distance to generate a new line
    void render(SDL_Renderer* renderer);
    void clean();
    void drawLine(int line[LINE_LENGTH], int roadStart, int roadWidth); // generates a sigle line of layout
    void restart(); // regenrates the entire layout and resets distance

    void laserHitObstacleCheck(SDL_Rect laserDestR, Laser* laser, int laserId);

    bool hitObstacle(int carBorderLeft, int carBorderRight); // returns true if payer hit an obstacle

private:
 
    int layout[30][40], width[30], roadStarts[30], distance = 0; 
    SDL_Texture *roadTex, *grassTex, *lineTex, *borderTex, *obstacleTex;
    SDL_Rect srcR, destR;
};
