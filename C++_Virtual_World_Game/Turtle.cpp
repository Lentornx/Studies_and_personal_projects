#include "Turtle.h"

Turtle::Turtle(int x, int y, World& world)
	:Animal(x, y, world)
{
	sign = 'T';
	name = "Turtle";
	str = 2;
	ini = 1;
	speciesId = 4;
}
Turtle::Turtle(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world)
	:Animal(str, ini, xPos, yPos, age, oId, moved, world)
{
	sign = 'T';
	name = "Turtle";
	speciesId = 1;
}
Animal* Turtle::MakeNewA(int x, int y) {
	Animal* newAnimal = new Turtle(x, y, world);
	return newAnimal;
}

void Turtle::TakeAction() {
	if (age != DEAD && !moved)
	{
		int changeX = 0, changeY = 0, rNum;
		rNum = rand() % 100;
		if (rNum < 25)
		{
			while (true)
			{
				rNum = (rand() % 100) % 4;
				if (rNum == 0) {
					changeX = -1;
				}
				else if (rNum == 1) {
					changeX = 1;
				}
				else if (rNum == 2) {
					changeY = -1;
				}
				else {
					changeY = 1;
				}
				if (STAYS_IN_BOUNDS)
					break;
				else {
					changeX = 0;
					changeY = 0;
				}
			}

			Organism* potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY);
			if (potentialCollision != nullptr) {
				Collision(*potentialCollision);
			}
			if (age != DEAD)
			{
				potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY); // recheck if collision changed the state of disputed tile
				if (potentialCollision == nullptr)
				{
					cout << name << " moved from tile (" << xPos << ", " << yPos << ") to tile (" << xPos + changeX << ", " << yPos + changeY << ")" << endl;
					xPos += changeX;
					yPos += changeY;
				}
			}
		}
		else
			cout << name << " from tile (" << xPos << ", " << yPos << ") stayed in place" << endl;
		moved = true;
	}
	if (age > 0) age++;
}

void Turtle::Win(Organism& otherCreature)
{
	if (deflected) {
		cout << " and " << name << " won! " << otherCreature.GetName() << " was pushed back" << endl;
		deflected = false;
	}
	else {
		cout << " and " << name << " won! " << otherCreature.GetName() << " was eaten" << endl;
		world.RmOrganism(otherCreature.GetOId());
		otherCreature.SetAge(DEAD);
	}
}

bool Turtle::Defended(Organism& attackingCreature) {
	if (attackingCreature.GetS() < 5) {
		deflected = true;
		return true;
	}
	return false;
}

Turtle::~Turtle() {
}