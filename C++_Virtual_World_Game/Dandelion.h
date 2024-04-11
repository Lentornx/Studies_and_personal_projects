#pragma once
#include "Plant.h"
class Dandelion : public Plant
{
public:
	Dandelion(int x, int y, World& world);
	Dandelion(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world);
	Plant* MakeNewP(int x, int y) override;
	~Dandelion() override;
};
