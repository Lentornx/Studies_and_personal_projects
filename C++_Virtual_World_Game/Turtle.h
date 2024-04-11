#pragma once
#include "Animal.h"
class Turtle : public Animal
{
public:
	Turtle(int x, int y, World& world);
	Turtle(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world);
	void TakeAction() override;
	Animal* MakeNewA(int x, int y) override;
	bool Defended(Organism& attackingCreature) override;
	void Win(Organism& otherCreature) override;
	~Turtle() override;

private:
	bool deflected;
};