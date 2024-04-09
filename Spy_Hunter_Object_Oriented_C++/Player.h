#pragma once

#include "Map.h"
#include "Defines.h"
#include "Laser.h"

extern "C" {
#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"
}

#ifdef __cplusplus
extern "C"
#endif

class Player
{
public:

    Player();
    ~Player();

    void init(SDL_Renderer* renderer);
    void respawn();
    void update(int* scoreToNextLife, Map* map);
    void render(SDL_Renderer* renderer);
    void clean(); 
    void restart(); 

    void shootLaser();

    void turnChange(int changeVal);
    void speedChange(int changeVal);

    int turn();
    int speed();
    int lifes();
    int immunityTimeLeft();
    int playerPos();

    bool isImmune();
    bool isGainingPoints();
    bool isOutOfRoad();

private:

    bool outOfRoad = false, gainingPoints = true;
    int lifesVal = LIFES_CAP, turnVal = NOT_TURNING, immunityTime = IMMUNITY_TIME, 
        speedVal = DEFAULT_SPEED, ammoVal = MAX_AMMO, reloadTime = 0,
        roadStartFront = INIT_ROAD_START, roadWidthFront = INIT_ROAD_WIDTH,
        roadStartRear = INIT_ROAD_START, roadWidthRear = INIT_ROAD_WIDTH;
    Laser *laser1;
    SDL_Texture* carTex,* ammoTex;
    SDL_Rect srcR, destR, ammoDestR;
};