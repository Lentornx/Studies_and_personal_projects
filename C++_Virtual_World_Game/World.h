#pragma once
#include <cstdlib>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <conio.h>
#include "Defines.h"
using namespace std;
class Organism;
class Human;

class World
{
public:
	World(int height, int width);

	int GetH() const;
	int GetW() const;
	void SetH(int h);
	void SetW(int w);

	void SetMap(int x, int y, char sign);

	void AddOrganism(Organism* newOrganism);
	void RmOrganism(int id);

	void StartGame();

	Organism* LookForCollision(int x, int y);

	void ResolveTurn();
	void Print() const;

	bool PlayerAlive();

	~World();

private:

	void sort();
	void Save();
	void Load();

	int height, width;
	int organismCount = 0;
	char** map;
	Organism** organisms;
	Human* player;
};