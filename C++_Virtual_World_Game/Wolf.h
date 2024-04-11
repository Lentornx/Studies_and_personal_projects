#pragma once
#include "Animal.h"
class Wolf: public Animal
{
public:
	Wolf(int x, int y, World& world);
	Wolf(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world);
	Animal* MakeNewA(int x, int y) override;
	~Wolf() override;
private:

};