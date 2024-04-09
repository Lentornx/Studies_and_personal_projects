#include "Player.h"

#include <stdio.h>
#include "TextureManager.h"

Player::Player()
{}
Player::~Player()
{}

void Player::init(SDL_Renderer* renderer)
{
    destR.y = SPAWN_POINT_Y;
    destR.x = SPAWN_POINT_X;
    destR.h = CAR_SIZE_Y;
    destR.w = CAR_SIZE_X;
    ammoDestR.y = AMMO_INTERFACE_Y;
    ammoDestR.h = TILE_SIZE;
    ammoDestR.w = TILE_SIZE;

    carTex = TextureManager::LoadTexture(CAR_IMAGE_PATH, renderer);
    ammoTex = TextureManager::LoadTexture("laser.bmp", renderer);
    laser1 = new Laser;
    laser1->init(renderer);
}

void Player::respawn()
{
    speedVal = MIN_SPEED;
    destR.y = SPAWN_POINT_Y;
    destR.x = SPAWN_POINT_X;
    lifesVal--;
    immunityTime = IMMUNITY_TIME;
}

void Player::update(int* scoreToNextLife, Map* map)
{
    map->roadInfo(&roadStartFront, &roadWidthFront, &roadStartRear, &roadWidthRear);

    laser1->move();
    for (int i = 0; i < MAX_AMMO; i++)
    {
        if ( laser1->isShot(i) );
            map->laserHitObstacleCheck(laser1->pos(i), laser1, i);
    }
   
    if (immunityTime)
        immunityTime--; // counting down immunity time for the player

    if (reloadTime)
        reloadTime--;

    else if (ammoVal < MAX_AMMO && !reloadTime)
    {
        ammoVal++;
        reloadTime = RELOAD_TIME;
    }

    if (*scoreToNextLife <= 0 && lifesVal < LIFES_CAP)
    {
        lifesVal++;
        *scoreToNextLife = SCORE_NEEDED_FOR_EXTRA_LIFE;
    } // adding 1 life when player reaches a point goal

    destR.x += turnVal;

    if ((!(CAR_BORDER_LEFT <= roadStartFront * TILE_SIZE + TILE_SIZE || CAR_BORDER_RIGHT >= (roadStartFront + roadWidthFront) * TILE_SIZE))
        && (!(CAR_BORDER_LEFT <= roadStartRear * TILE_SIZE + TILE_SIZE || CAR_BORDER_RIGHT >= (roadStartRear + roadWidthRear) * TILE_SIZE)))
    {
        gainingPoints = true;
    }
    else 
        gainingPoints = false;

    if ( (CAR_BORDER_LEFT <= roadStartFront * TILE_SIZE || CAR_BORDER_RIGHT >= (roadStartFront + roadWidthFront) * TILE_SIZE + TILE_SIZE)
        || (CAR_BORDER_LEFT <= roadStartRear * TILE_SIZE || CAR_BORDER_RIGHT >= (roadStartRear + roadWidthRear) * TILE_SIZE + TILE_SIZE) )
    {
        outOfRoad = true;
    } 
    else
        outOfRoad = false;
}

void Player::render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, carTex, NULL, &destR);
    laser1->render(renderer);
    ammoDestR.x = AMMO_INTERFACE_X;
    for (int i = 0; i < ammoVal; i++)
    {
        SDL_RenderCopy(renderer, ammoTex, NULL, &ammoDestR); 
        ammoDestR.x += 2 * TILE_SIZE;
    }
   
}

void Player::clean()
{
    SDL_DestroyTexture(carTex);
    SDL_DestroyTexture(ammoTex);
    laser1->clean();
}

void Player::restart()
{
    destR.y = SPAWN_POINT_Y;
    destR.x = SPAWN_POINT_X;
    destR.h = CAR_SIZE_Y;
    destR.w = CAR_SIZE_X;
    lifesVal = LIFES_CAP;
    turnVal = NOT_TURNING;
    immunityTime = IMMUNITY_TIME;
    speedVal = DEFAULT_SPEED;
    outOfRoad = false;
    gainingPoints = true;
    for (int i = 0; i < MAX_AMMO; i++)
        laser1->restart(i);
}

void Player::shootLaser()
{
    for (int i = 0; i < MAX_AMMO; i++)
    {
        if (!laser1->isShot(i) && ammoVal)
        {
            laser1->shoot(CAR_BORDER_LEFT, i);
            ammoVal--;
            reloadTime = RELOAD_TIME;
            break;
        }
    }
    
}

void Player::turnChange(int changeVal)
{
    turnVal = changeVal;
}

void Player::speedChange(int changeVal)
{
    if (changeVal == INCREASE)
        speedVal *= 2;
    else if (changeVal == DECREASE)
        speedVal /= 2;
}

int Player::turn()
{
    return turnVal;
}

int Player::speed()
{
    return speedVal;
}

int Player::lifes()
{ 
    return lifesVal;
}

int Player::immunityTimeLeft()
{
    return immunityTime;
}

int Player::playerPos()
{
    return destR.x;
}

bool Player::isImmune()
{
    if (immunityTime)
        return true;
    else
        return false;
}

bool Player::isGainingPoints()
{
    return gainingPoints;
}

bool Player::isOutOfRoad()
{
    return outOfRoad;
}
