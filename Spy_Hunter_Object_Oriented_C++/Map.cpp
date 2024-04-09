#include "Map.h"
#include "TextureManager.h"
#include "Defines.h"

Map::Map()
{}
Map::~Map()
{}

void Map::generateRoadBorders(int *roadStart, int *roadWidth)
{
    static int roadChangeTimer = 0, roadChangeValue, roadChangeInterval = 0;

    if (roadChangeTimer >= roadChangeInterval)
    {
        roadChangeTimer = 0;
        roadChangeInterval = (rand() % 15) + 5;
        roadChangeValue = RANDOM_INT_FROM_NEGATIVE_ZERO_TO_TEN;
    }   
    roadChangeTimer++;
    //printf(" VAL = %d ", roadChangeValue);
    if (*roadStart >= LINE_START_MIN && *roadStart <= LINE_START_MAX - *roadWidth)
    {
        if (roadChangeValue <= 3)
        {
            //printf(" <= 3 \n");
            (*roadStart)++; 
        }
        else if (roadChangeValue <= 7)
        {
            //printf(" <= 7 \n");
            (*roadStart)--;  
        }
        else if (roadChangeValue == 8 && *roadWidth >= MIN_ROAD_WIDTH)
        {
            //printf(" == 8 \n");
            (*roadStart)++;
            *roadWidth -= 2;
        }
        else if (roadChangeValue == 9 && *roadWidth <= MAX_ROAD_WIDTH)
        {
            //printf(" == 9 ");
            if (*roadWidth + *roadStart < LINE_START_MAX && *roadStart > LINE_START_MIN)
            {
                //printf(" V1 \n");
                (*roadStart)--;
                *roadWidth += 2;
            }
            else if (*roadWidth + *roadStart >= LINE_START_MAX)
            {
                //printf(" V2 \n");
                (*roadStart)--;
                (*roadWidth)++;
            }
            else 
            {
                //printf(" V3 \n");
                (*roadWidth)++;
            }
        }
    }

    if (*roadStart < LINE_START_MIN)
        *roadStart = LINE_START_MIN;
    else if (*roadStart > LINE_START_MAX - *roadWidth)
        *roadStart = LINE_START_MAX - *roadWidth;
    if (*roadWidth + *roadStart >= LINE_START_MAX)
        *roadWidth = LINE_START_MAX - *roadStart;
    else if (*roadWidth < MIN_ROAD_WIDTH)
    {
        *roadWidth += 2;
        (*roadStart) --;
    }
    if (*roadWidth > MAX_ROAD_WIDTH)
    {
        (*roadStart)++;
        (*roadWidth)--;
    }
}

void Map::roadInfo(int* roadStartFront, int* roadWidthFront, int* roadStartRear, int* roadWidthRear)
{
    *roadStartFront = roadStarts[CAR_FRONT];
    *roadWidthFront = width[CAR_FRONT];
    *roadStartRear = roadStarts[CAR_REAR];
    *roadWidthRear = width[CAR_REAR];
}

void Map::drawLine(int line[LINE_LENGTH], int roadStart, int roadWidth)
{
    static int obstacleTimer = 0;

    int obstacleChance = rand() % 100, obstaclePos = 0;

    if ( !(obstacleChance % 10) && (obstacleTimer > MIN_OBSTACLE_RESPAWN_TIME) && roadWidth >= (MAX_ROAD_WIDTH + MIN_ROAD_WIDTH)/2)
    {
        obstacleTimer = 0;
        obstaclePos = (rand() % (roadWidth - 2) ) + 1 + roadStart;
    }
    obstacleTimer++;
    
    for (int i = LINE_START; i < roadStart; i++)
    {
        line[i] = GRASS;
    }

    line[roadStart] = BORDER;

    for (int i = roadStart + 1; i < roadStart + roadWidth; i++)
    {
        if (obstaclePos == i)
            line[i] = OBSTACLE;
        else
            line[i] = ROAD;
    }

    line[roadStart + roadWidth] = BORDER;

    for (int i = roadStart + roadWidth + 1; i < LINE_LENGTH; i++)
    {
        line[i] = GRASS;
    }
}

void Map::restart()
{
    distance = 0;
    for (int i = 0; i <= LAYOUT_LINES_COUNT; i++)
    {
        roadStarts[i] = INIT_ROAD_START;
        width[i] = INIT_ROAD_WIDTH;
        Map::drawLine(layout[i], roadStarts[i], width[i]);
    }
}

void Map::init(SDL_Renderer* renderer)
{
    destR.h = TILE_SIZE;
    destR.w = TILE_SIZE;
    borderTex = TextureManager::LoadTexture("border.bmp", renderer);
    grassTex = TextureManager::LoadTexture("grass.bmp", renderer);
    roadTex = TextureManager::LoadTexture("road.bmp", renderer);
    lineTex = TextureManager::LoadTexture("line.bmp", renderer);
    obstacleTex = TextureManager::LoadTexture("Obstacle.bmp", renderer);
    Map::restart();
}

void Map::move() 
{
    for (int y = LAYOUT_LINES_COUNT; y > 0; y--)
    {
        for (int x = LINE_START; x < LINE_LENGTH; x++)
        {
            layout[y][x] = layout[y-1][x];
        }
        roadStarts[y] = roadStarts[y-1];
        width[y] = width[y-1];
    }
    Map::generateRoadBorders(&roadStarts[NEW_LINE], &width[NEW_LINE]);
    Map::drawLine(layout[NEW_LINE], roadStarts[NEW_LINE], width[NEW_LINE]);
}

void Map::update(int speed)
{
    if (distance >= TILE_SIZE)
        {
            Map::move();
            distance = 0;
        }
    distance += speed;
}

void Map::render( SDL_Renderer* renderer)
{
    for (int y = 0; y <= LAYOUT_LINES_COUNT; y++)
    {
        destR.y = (y*TILE_SIZE) + distance;
        for (int x = LINE_START; x < LINE_LENGTH; x++)
        {
            destR.x = x * TILE_SIZE;
            switch (layout[y][x]) {
            case GRASS:
                SDL_RenderCopy(renderer, grassTex, NULL, &destR);
                break;
            case ROAD:
                SDL_RenderCopy(renderer, roadTex, NULL, &destR);
                break;
            case BORDER:
                SDL_RenderCopy(renderer, borderTex, NULL, &destR);
                break;
            case LINE:
                SDL_RenderCopy(renderer, lineTex, NULL, &destR);
                break;
            case OBSTACLE:
                SDL_RenderCopy(renderer, obstacleTex, NULL, &destR);
                break;
            };
        }
    }
}

void Map::clean()
{
    SDL_DestroyTexture(roadTex);
    SDL_DestroyTexture(grassTex);
    SDL_DestroyTexture(lineTex);
    SDL_DestroyTexture(borderTex);
}

void Map::laserHitObstacleCheck(SDL_Rect laserDestR, Laser* laser, int laserId)
{
    for (int i = NEW_LINE; i <= LAYOUT_LINES_COUNT; i++)
    {
        for (int i2 = LINE_START; i2 < LINE_LENGTH; i2++)
        {
            if (layout[i][i2] == OBSTACLE)
                if (sqrt(abs(laserDestR.x - i2 * TILE_SIZE) + abs(laserDestR.y - i * TILE_SIZE) < TILE_SIZE))
                {
                    layout[i][i2] = ROAD;
                    laser->restart(laserId);
                }
        }
    }

}

bool Map::hitObstacle(int carBorderLeft, int carBorderRight)
{
    for (int i = CAR_FRONT; i < CAR_REAR; i++)
    {
        for (int i2 = roadStarts[i]; i2 < roadStarts[i] + width[i]; i2++)
        {
            if (layout[i][i2] == OBSTACLE)
            {
                if (carBorderRight >= i2 * TILE_SIZE + TILE_SIZE / 2 && carBorderLeft <= i2 * TILE_SIZE + TILE_SIZE / 2)
                    return true;
            }
        }
    }
    return false;
}

