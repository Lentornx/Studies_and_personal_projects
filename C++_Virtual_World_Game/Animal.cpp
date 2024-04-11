#include "Animal.h"

Animal::Animal(int x, int y, World& world)
	:Organism(x,y,world) {}
Animal::Animal(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world) 
	:Organism(str, ini, xPos, yPos, age, oId, moved, world) {}

bool Animal::Defended(Organism& attackingCreature) {
	if (str > attackingCreature.GetS())
		return true;
	return false;
}

void Animal::Win(Organism& otherCreature)
{
	cout << " and " << name << " won! " << otherCreature.GetName() << " was eaten" << endl;
	world.RmOrganism(otherCreature.GetOId());
	otherCreature.SetAge(DEAD);
}

void Animal::Procreate() {
	int rNum;
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
			if (potentialCollision == nullptr)
			{
				Animal* newAnimal = MakeNewA(xPos + changeX, yPos + changeY);
				world.AddOrganism(newAnimal);
				cout << " and spawned offspring on tile (" << xPos + changeX << ", " << yPos + changeY << ")" << endl;
				break;
			}
		}
		if (triedDown && triedUp && triedLeft && triedRight)
		{
			cout << ", but had no adjacent tiles to spawn offspring to" << endl;
			break;
		}
	}
}

void Animal::TakeAction() {
	if (age != DEAD && !moved)
	{
		int changeX = 0, changeY = 0, rNum;
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
		moved = true;
	}
	if (age>0) age++;
}

void Animal::Collision(Organism& defendingCreature) {
	if (defendingCreature.GetSId() == speciesId)
	{
		cout << name << " from tile (" << xPos << ", " << yPos << ") encountered a mate on tile (" << defendingCreature.GetX() << ", " << defendingCreature.GetY() << ")";
		if (defendingCreature.HasMoved()) {
			cout << ", but the mate has already moved this turn" << endl;
		}
		else {
			Procreate();

			Animal& defendingCreatureCast = (Animal&)defendingCreature;
			cout << defendingCreatureCast.GetName() << " on tile(" << defendingCreature.GetX() << ", " << defendingCreature.GetY() << ") tried too";
			defendingCreatureCast.Procreate();
			defendingCreature.SetHasMoved(true);
		}
	}
	else
	{
		cout << name << " from tile (" << xPos << ", " << yPos << ") encountered a " << defendingCreature.GetName() << " on tile (" << defendingCreature.GetX() << ", " << defendingCreature.GetY() << ")";
		if (defendingCreature.Defended(*this))
			defendingCreature.Win(*this);
		else
			Win(defendingCreature);
	}
}

void Animal::Print() {
	world.SetMap(xPos, yPos, sign);
}

Animal::~Animal() {}