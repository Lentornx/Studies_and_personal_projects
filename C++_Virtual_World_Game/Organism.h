#pragma once
#include "World.h"
using namespace std;

class Organism
{
public:
	Organism (int x, int y, World& world);
	Organism (int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world);

	int GetS() const;
	void SetS(int strength);

	int GetI() const;
	void SetI(int initiative);

	int GetX() const;
	void SetX(int xPos);

	int GetY() const;
	void SetY(int yPos);

	World& GetW() const;

	int GetSId() const;

	int GetOId() const;
	void SetOId(int oId);

	int GetAge() const;
	void SetAge(int age);

	string GetName();

	bool HasMoved();
	void SetHasMoved(bool moved);

	virtual void Win(Organism& otherCreature) = 0;
	virtual bool Defended(Organism& attackingCreature) = 0;
	virtual void TakeAction() = 0;
	virtual void Print() = 0;

	virtual ~Organism();

protected:
	int str, ini, xPos, yPos, age = 0, speciesId, oId;
	World& world;
	char sign; 
	string name;
	bool moved = true;
};
