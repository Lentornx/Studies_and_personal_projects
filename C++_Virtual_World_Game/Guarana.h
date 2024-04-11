#pragma once
#include "Plant.h"
class Guarana: public Plant
{
public:
	Guarana(int x, int y, World& world);
	Guarana(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world);
	Plant* MakeNewP(int x, int y) override;
	bool Defended(Organism& attackingCreature) override;
	~Guarana() override;
};
