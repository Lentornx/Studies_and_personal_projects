#include "Hogweed.h"

Hogweed::Hogweed(int x, int y, World& world)
	:Plant(x, y, world)
{
	sign = 'H';
	name = "Hogweed";
	str = 10;
	speciesId = 10;
	spreadChance = 5;
	spreadCount = 1;
}
Hogweed::Hogweed(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world)
	:Plant(str, ini, xPos, yPos, age, oId, moved, world)
{
	sign = 'H';
	name = "Hogweed";
	spreadChance = 5;
	spreadCount = 1;
}
Plant* Hogweed::MakeNewP(int x, int y) {
	Plant* newPlant = new Hogweed(x, y, world);
	return newPlant;
}
void Hogweed::TakeAction() {
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
		cout << name << " from tile (" << xPos << ", " << yPos << ")is killing animals around it!" << endl;
		for(int changeX = -1; changeX <= 1;changeX ++)
			for (int changeY = -1; changeY <= 1; changeY ++)
				if((changeX == 0 && changeY != 0) || (changeY == 0 && changeX != 0))
					if (STAYS_IN_BOUNDS)
					{
						Organism* potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY);
						if (potentialCollision != nullptr)
							if (potentialCollision->GetI() != 0) // only animals have ini == 0
							{
								cout << potentialCollision->GetName()<< " from tile (" << xPos + changeX << ", " << yPos + changeY << ") perished" << endl;
								world.RmOrganism(potentialCollision->GetOId());
							}
					}
		age++;
	}
}
Hogweed::~Hogweed() {
}