#include "Human.h"
#include <Windows.h>

Human::Human(int x, int y, World& world)
	:Animal(x, y, world)
{
	sign = 'Y';
	name = "Human";
	str = 5;
	ini = 4;
	speciesId = 11;
}
Human::Human(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world)
	:Animal(str, ini, xPos, yPos, age, oId, moved, world)
{
	sign = 'Y';
	name = "Human";
	speciesId = 11;
}
Animal* Human::MakeNewA(int x, int y) { return nullptr;}

int Human::GetCd() {
	return cooldown;
}
void Human::SetCd(int cooldown) {
	this->cooldown = cooldown;
}
int Human::GetP() {
	return powerLeft;
}
void Human::SetP(int powerLeft) {
	this->powerLeft = powerLeft;
}

void Human::SetAction(char action) {
	this->action = action;
}

bool Human::MadeFirstMove() {
	return madeFirstMove;
}

void Human::TakeAction() {
	if (action == 'f' && !cooldown && !madeFirstMove)
	{
		powerLeft = 5;
		cooldown = 10;
		cout << "Antelope's speed activated!" << endl;
		world.Print();
	}
	else if (!madeFirstMove)
	{
		if (action == 'w')
			changeY--;
		else if (action == 's')
			changeY++;
		else if (action == 'a')
			changeX--;
		else if (action == 'd')
			changeX++;
		if (STAYS_IN_BOUNDS && (changeX || changeY))
			madeFirstMove = true;

		if (powerLeft > 0)
		{
			int rNum = rand() % 2;
			if (powerLeft >= 3 || rNum)
			{
				specialActivated = true;
				cout << endl << "Antelope's speed active! You may choose to move to another tile if you wish, press k to end turn instaed" << endl;
				world.Print();
			}
			else
			{
				specialActivated = false;
			}
		}
		else
			madeSecondMove = true;
		
	}
	else if (!madeSecondMove)
	{
		if (specialActivated)
		{
			if (action == 'w')
				changeY--;
			else if (action == 's')
				changeY++;
			else if (action == 'a')
				changeX--;
			else if (action == 'd')
				changeX++;
			else if (action == 'k')
				madeSecondMove = true;
		}
		if (STAYS_IN_BOUNDS && (changeX || changeY))
			madeSecondMove = true;
		else
		{
			cout << " wrong input, try again!" << endl;
			changeX = 0;
			changeY = 0;
			madeFirstMove = false;
			madeSecondMove = false;
		}
	}
	if ((madeFirstMove && !powerLeft) || (madeSecondMove)) {
		Organism* potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY);
		if (potentialCollision != nullptr) {
			Collision(*potentialCollision);
		}
		if (age != DEAD)
		{
			potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY);
			if (potentialCollision == nullptr)
			{
				cout << name << " moved from tile (" << xPos << ", " << yPos << ") to tile (" << xPos + changeX << ", " << yPos + changeY << ")" << endl;
				xPos += changeX;
				yPos += changeY;
			}
		}
		moved = true;
		if (age > 0) age++;
		if (cooldown)
			cooldown--;
		if (powerLeft)
			powerLeft--;
		changeX = 0;
		changeY = 0;
		madeFirstMove = false;
		madeSecondMove = false;
		specialActivated = false;
	}
}

Human::~Human() {
}