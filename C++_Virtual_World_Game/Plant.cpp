#include "Plant.h"

Plant::Plant(int x, int y, World& world) 
	: Organism(x,y,world) {
	ini = 0;
}
Plant::Plant(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world)
	:Organism(str, ini, xPos, yPos, age, oId, moved, world) {}

void Plant::TakeAction() {
	if (!moved && age > 0)
	{
		int rNum, spreadsAttempted = 0;
		while (spreadsAttempted != spreadCount)
		{
			rNum = rand() % 100;
			cout << name << " from tile (" << xPos << ", " << yPos << ") tried spreading";
			if (rNum >= 99 - spreadChance)
				Spread();
			else
				cout << ", but failed" << endl;
			spreadsAttempted++;
		}
		age++;
	}
}

void Plant::Win(Organism& otherCreature) {
	cout << " and " << otherCreature.GetName() << " died while eating it! Both perished" << endl;
	world.RmOrganism(otherCreature.GetOId());
	world.RmOrganism(oId);
	otherCreature.SetAge(DEAD);
	age = DEAD;
}

bool Plant::Defended(Organism& attackingCreature) {
	if (str > attackingCreature.GetS())
		return true;
	return false;
}

void Plant::Spread() {
	bool triedLeft = false, triedRight = false, triedUp = false, triedDown = false;
	while (true)
	{
		int changeX = 0, changeY = 0, rNum;
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
			if (potentialCollision == nullptr)
			{
				Plant* newPlant = MakeNewP(xPos + changeX, yPos + changeY);
				world.AddOrganism(newPlant);
				cout << " and spread to tile (" << xPos + changeX << ", " << yPos + changeY << ")" << endl;
				break;
			}
		}
		else {
			changeX = 0;
			changeY = 0;
		}
		if (triedDown && triedUp && triedLeft && triedRight)
		{
			cout << ", but had no adjacent tiles to spread to" << endl;
			break;
		}
	}
}
void Plant::Print() {
	world.SetMap(xPos, yPos, sign);
}

Plant::~Plant() {}