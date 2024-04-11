#pragma once
#include "Organism.h"

class Animal: public Organism
{
public:
	Animal(int x, int y, World& world);
	Animal(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world);

	virtual void TakeAction() override;
	virtual Animal* MakeNewA(int x, int y) = 0;
	void Procreate();
	virtual void Collision(Organism& defendingCreature);
	void Print() override;
	virtual bool Defended(Organism& attackingCreature) override;
	virtual void Win(Organism& otherCreature) override;

	~Animal() override;
};
 