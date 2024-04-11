#include "Sheep.h"

Sheep::Sheep(int x, int y, World& world) 
	:Animal(x,y,world) 
{
	sign = 'S';
	name = "Sheep";
	str = 4;
	ini = 4;
	speciesId = 1;
}
Sheep::Sheep(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world)
	:Animal(str, ini, xPos, yPos, age, oId, moved, world)
{
	sign = 'S';
	name = "Sheep";
	speciesId = 1;
}
Animal* Sheep::MakeNewA(int x, int y) {
	Animal* newAnimal = new Sheep(x, y, world);
	return newAnimal;
}
Sheep::~Sheep() {
}