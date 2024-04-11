#pragma once
#include "Plant.h"
class Wolfberry : public Plant
{
public:
	Wolfberry(int x, int y, World& world);
	Wolfberry(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world);
	Plant* MakeNewP(int x, int y) override;
	~Wolfberry() override;
};
