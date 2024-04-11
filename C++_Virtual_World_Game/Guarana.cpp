#include "Guarana.h"

Guarana::Guarana(int x, int y, World& world)
	:Plant(x, y, world)
{
	sign = 'U';
	name = "Guarana";
	str = 0;
	speciesId = 7;
	spreadChance = 40;
	spreadCount = 1;
}
Guarana::Guarana(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world)
	:Plant(str, ini, xPos, yPos, age, oId, moved, world)
{
	sign = 'U';
	name = "Guarana";
	spreadChance = 40;
	spreadCount = 1;
	speciesId = 7;
}
Plant* Guarana::MakeNewP(int x, int y) {
	Plant* newPlant = new Guarana(x, y, world);
	return newPlant;
}
bool Guarana::Defended(Organism& attackingCreature) {
	int newStr = attackingCreature.GetS() + 3;
	attackingCreature.SetS(newStr); 
	cout << ", which is granting strength upon being eaten,";
	if (str > attackingCreature.GetS())
		return true;
	return false;
}
Guarana::~Guarana() {
}