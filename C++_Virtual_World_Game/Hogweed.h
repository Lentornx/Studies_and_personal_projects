#pragma once
#include "Plant.h"
class Hogweed : public Plant
{
public:
	Hogweed(int x, int y, World& world);
	Hogweed(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world);
	Plant* MakeNewP(int x, int y) override;
	void TakeAction() override;
	~Hogweed() override;
};
