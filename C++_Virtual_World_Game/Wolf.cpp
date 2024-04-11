#include "Wolf.h"

Wolf::Wolf(int x, int y, World& world)
	:Animal(x, y, world)
{
	sign = 'W';
	name = "Wolf";
	str = 9;
	ini = 5;
	speciesId = 2;
}
Wolf::Wolf(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world)
	:Animal(str, ini, xPos, yPos, age, oId, moved, world)
{
	sign = 'W';
	name = "Wolf";
	speciesId = 2;
}
Animal* Wolf::MakeNewA(int x, int y) {
	Animal* newAnimal = new Wolf(x, y, world);
	return newAnimal;
}
Wolf::~Wolf() {
}