#pragma once
#include "Animal.h"
class Sheep: public Animal
{
public:
	Sheep(int x, int y, World& world);
	Sheep(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world);
	Animal* MakeNewA(int x, int y) override;
	~Sheep() override;
};