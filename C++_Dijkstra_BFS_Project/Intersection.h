#pragma once
#include <iostream>
#include "Destination.h"
#include <math.h>
using namespace std;
class Intersection
{
public:
	Intersection(char* name, int x, int y);

	char* GetName();
	int GetX();
	int GetY();

	void addDest(Intersection* dest, int length);
	void printNeighbours();
	bool CompareName(char* tested);

	bool WasVisited();
	Intersection* GetPrev();
	int GetDist();

	void SetVisited(bool visited);
	void SetPrev(Intersection* prev);
	void SetDist(int dist);

	void MeasureNeighbours();

	~Intersection();

private:
	char* name;
	int x, y;
	Destination* head = nullptr;
	bool visited;
	Intersection* prev;
	int dist;
};