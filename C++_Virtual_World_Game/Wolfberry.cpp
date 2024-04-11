#include "Wolfberry.h"

Wolfberry::Wolfberry(int x, int y, World& world)
	:Plant(x, y, world)
{
	sign = 'B';
	name = "Wolfberry";
	str = 99;
	speciesId = 9;
	spreadChance = 20;
	spreadCount = 1;
}
Wolfberry::Wolfberry(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world)
	:Plant(str, ini, xPos, yPos, age, oId, moved, world)
{
	sign = 'B';
	name = "Wolfberry";
	spreadChance = 20;
	spreadCount = 1;
	speciesId = 9;
}
Plant* Wolfberry::MakeNewP(int x, int y) {
	Plant* newPlant = new Wolfberry(x, y, world);
	return newPlant;
}
Wolfberry::~Wolfberry() {
}