#include "Grass.h"

Grass::Grass(int x, int y, World& world)
	:Plant(x, y, world)
{
	sign = 'G';
	name = "Grass";
	str = 0;
	speciesId = 6;
	spreadChance = 50;
	spreadCount = 1;
}
Grass::Grass(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world)
	:Plant(str, ini, xPos, yPos, age, oId, moved, world) 
{
	sign = 'G';
	name = "Grass";
	spreadChance = 50;
	spreadCount = 1;
	speciesId = 6;
}

Plant* Grass::MakeNewP(int x, int y) {
	Plant* newPlant = new Grass(x, y, world);
	return newPlant;
}
Grass::~Grass() {
}