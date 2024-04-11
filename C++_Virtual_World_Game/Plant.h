#pragma once
#include "Organism.h"

class Plant : public Organism
{
public:
	Plant(int x, int y, World& world);
	Plant(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world);
	virtual void TakeAction() override;
	virtual Plant* MakeNewP(int x, int y) = 0;
	virtual void Win(Organism& otherCreature) override;
	virtual bool Defended(Organism& attackingCreature) override;
	void Print() override;
	void Spread();
	~Plant() override;
protected:
	int spreadChance, spreadCount; 
};
