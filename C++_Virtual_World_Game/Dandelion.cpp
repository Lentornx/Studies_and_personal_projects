#include "Dandelion.h"

Dandelion::Dandelion(int x, int y, World& world)
	:Plant(x, y, world)
{
	sign = 'D';
	name = "Dandelion";
	str = 0;
	speciesId = 8;
	spreadChance = 30;
	spreadCount = 3;
}
Dandelion::Dandelion(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world)
	:Plant(str, ini, xPos, yPos, age, oId, moved, world)
{
	sign = 'D';
	name = "Dandelion";
	spreadChance = 30;
	spreadCount = 3;
	speciesId = 8;
}
Plant* Dandelion::MakeNewP(int x, int y) {
	Plant* newPlant = new Dandelion(x, y, world);
	return newPlant;
}
Dandelion::~Dandelion() {
}