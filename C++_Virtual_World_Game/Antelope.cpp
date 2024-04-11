#include "Antelope.h"

Antelope::Antelope(int x, int y, World& world)
	:Animal(x, y, world)
{
	sign = 'A';
	name = "Antelope";
	str = 4;
	ini = 4;
	speciesId = 5;
}
Antelope::Antelope(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world)
	:Animal(str, ini, xPos, yPos, age, oId, moved, world)
{
	sign = 'A';
	name = "Antelope";
	speciesId = 5;
}
Animal* Antelope::MakeNewA(int x, int y) {
	Animal* newAnimal = new Antelope(x, y, world);
	return newAnimal;
}
bool Antelope::Defended(Organism& attackingCreature) {
	if (str > attackingCreature.GetS()) {
		return true;
	}
	else 
	{
		int rNum2 = (rand() % 100) % 2;
		if (rNum2) {
			avoided = true;
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
				{
					Organism* potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY);
					if (potentialCollision == nullptr || (xPos + changeX == attackingCreature.GetX() && yPos + changeY == attackingCreature.GetY()) )
					{
						xPos += changeX;
						yPos += changeY;
						return true;
					}
				}
				else {
					changeX = 0;
					changeY = 0;
				}
			}
		}
	}
	return false;
}

void Antelope::Win(Organism& otherCreature)
{
	if (avoided) {
		cout << " and " << name << " ran away! It went to tile (" << xPos << ", " << yPos << ")" << endl;
		avoided = false;
	}
	else {
		cout << " and " << name << " won! " << otherCreature.GetName() << " was eaten" << endl;
		world.RmOrganism(otherCreature.GetOId());
		otherCreature.SetAge(DEAD);
	}
}
void Antelope::TakeAction() {
	if (age != DEAD && !moved)
	{
		int changeX = 0, changeY = 0, rNum, rNum2;
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

			rNum2 = (rand() % 60) % 4;
			if (rNum2 == 0) {
				changeX += -1;
			}
			else if (rNum2 == 1) {
				changeX += 1;
			}
			else if (rNum2 == 2) {
				changeY += -1;
			}
			else {
				changeY += 1;
			}
			if (STAYS_IN_BOUNDS && (changeX != 0 || changeY != 0))
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
		if (age != DEAD && avoided == false)
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
		avoided = false;
	}
	if (age > 0) age++;
}

void Antelope::Collision(Organism& defendingCreature) {
	if (defendingCreature.GetSId() == speciesId)
	{
		cout << name << " from tile (" << xPos << ", " << yPos << ") encountered a mate on tile (" << defendingCreature.GetX() << ", " << defendingCreature.GetY() << ")";
		if (defendingCreature.HasMoved()) {
			cout << ", but the mate has already moved this turn" << endl;
		}
		else {
			Procreate();

			Animal& defendingCreatureCast = (Animal&)defendingCreature;
			cout << defendingCreatureCast.GetName() << " on tile(" << defendingCreature.GetX() << ", " << defendingCreature.GetY() << ") tries spawning their offspring too";
			defendingCreatureCast.Procreate();
			defendingCreature.SetHasMoved(true);
		}
	}
	else
	{
		cout << name << " from tile (" << xPos << ", " << yPos << ") encountered a " << defendingCreature.GetName() << " on tile (" << defendingCreature.GetX() << ", " << defendingCreature.GetY() << ") ";
		if (!defendingCreature.Defended(*this))
			Win(defendingCreature);
		else
		{
			int rNum3 = (rand() % 26) % 2;
			if (rNum3)
				defendingCreature.Win(*this);
			else
			{
				cout << name << " tries to run away, ";
				int rNum2 = (rand() % 100) % 2;
				if (rNum2)
				{
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
							Organism* potentialCollision = world.LookForCollision(defendingCreature.GetX() + changeX, defendingCreature.GetY() + changeY);
							if (potentialCollision == nullptr)
							{
								avoided = true;
								break;
							}
						}
						else {
							changeX = 0;
							changeY = 0;
						}
						if (triedDown && triedUp && triedLeft && triedRight)
						{
							cout << "but has nowhere to run to " << endl;
							break;
						}
					}
				}
				if (avoided) {
					cout << "and succeeds!";
					Win(defendingCreature);
				}
				else {
					cout << "and fails!";
					defendingCreature.Win(*this);
					
				}
			}
		}
	}
}

Antelope::~Antelope() {
}