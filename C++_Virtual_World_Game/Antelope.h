#pragma once
#include "Animal.h"
class Antelope : public Animal
{
public:
	Antelope(int x, int y, World& world);
	Antelope(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world);

	void TakeAction() override;
	Animal* MakeNewA(int x, int y) override;
	bool Defended(Organism& attackingCreature) override;
	void Win(Organism& otherCreature) override;
	void Collision(Organism& defendingCreature) override;
	~Antelope() override;

private:
	bool avoided = false;
};