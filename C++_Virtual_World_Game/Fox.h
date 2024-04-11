#pragma once
#include "Animal.h"
class Fox : public Animal
{
public:
	Fox(int x, int y, World& world);
	Fox(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world);
	void TakeAction() override;
	Animal* MakeNewA(int x, int y) override;
	~Fox() override;
};