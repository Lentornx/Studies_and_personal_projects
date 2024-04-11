#pragma once
#include "Plant.h"
class Grass : public Plant
{
public:
	Grass(int x, int y, World& world);
	Grass(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world);
	Plant* MakeNewP(int x, int y) override;
	~Grass() override;
};
