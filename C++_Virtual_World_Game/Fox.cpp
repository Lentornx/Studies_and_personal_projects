#include "Fox.h"

Fox::Fox(int x, int y, World& world)
	:Animal(x, y, world)
{
	sign = 'F';
	name = "Fox";
	str = 3;
	ini = 7;
	speciesId = 3;
}
Fox::Fox(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world)
	:Animal(str, ini, xPos, yPos, age, oId, moved, world)
{
	sign = 'F';
	name = "Fox";
	speciesId = 3;
}
Animal* Fox::MakeNewA(int x, int y) {
	Animal* newAnimal = new Fox(x, y, world);
	return newAnimal;
}
void Fox::TakeAction() {
	if (age != DEAD && !moved)
	{
		int changeX = 0, changeY = 0, rNum;
		bool triedLeft = false, triedRight = false, triedUp = false, triedDown = false;
		while (true)
		{
			int changeX = 0, changeY = 0;
			rNum = (rand() % 100) % 4;
			if (rNum == 0) {
				if (triedLeft)
					continue;
				else
					triedLeft = true;
				changeX = -1;
			}
			else if (rNum == 1) {
				if (triedRight)
					continue;
				else
					triedRight = true;
				changeX = 1;
			}
			else if (rNum == 2) {
				if (triedUp)
					continue;
				else
					triedUp = true;
				changeY = -1;
			}
			else {
				if (triedDown)
					continue;
				else
					triedDown = true;
				changeY = 1;
			}
			if (STAYS_IN_BOUNDS)
			{
				Organism* potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY);
				if (potentialCollision != nullptr)
				{
					if (potentialCollision->GetS() <= str)
					{
						Collision(*potentialCollision);
						potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY); // recheck if collision changed the state of disputed tile
						if (potentialCollision == nullptr)
						{
							cout << name << " moved from tile (" << xPos << ", " << yPos << ") to tile (" << xPos + changeX << ", " << yPos + changeY << ")" << endl;
							xPos += changeX;
							yPos += changeY;
							break;
						}
					}
				}
				else
				{
					cout << name << " moved from tile (" << xPos << ", " << yPos << ") to tile (" << xPos + changeX << ", " << yPos + changeY << ")" << endl;
					xPos += changeX;
					yPos += changeY;
					break;
				}
			}
			else {
				changeX = 0;
				changeY = 0;
			}
			if (triedDown && triedUp && triedLeft && triedRight)
			{
				cout << name << " from tile(" << xPos << ", " << yPos << "), but has nowhere safe to go!" << endl;
				break;
			}
		}
		moved = true;
	}
	if (age > 0) age++;
}


Fox::~Fox() {
}