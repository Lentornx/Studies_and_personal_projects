#pragma once
#define STAYS_IN_BOUNDS  xPos + changeX < world.GetW() && yPos + changeY < world.GetH() &&  xPos + changeX >= 0 && yPos + changeY >= 0
#define DEAD -1