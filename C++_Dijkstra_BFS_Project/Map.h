#pragma once
#include <iostream>
#include "Intersection.h"
#include "Defines.h"
#include "PointQueue.h"
using namespace std;

class Map
{
public:
	Map();
	void ParseHashMap();
	char* ParseCityName(int x, int y);
	void AddToHashMap(Intersection* tmp);
	void ParseGraph();
	char* GetInput();

	int CoordToHash(int x, int y);
	int NameToHash(char* name);

	Intersection* LookByCoord(int x, int y);
	Intersection* LookByName(char* name);

	void Dijkstra(Intersection* source, char* dest, bool showPath);
	void OutputPath(Intersection* currentI);

	~Map();

private:
	int w, h, cityCount = 0;
	char** layout;
	int** pathMarker, * pointX, * pointY;
	Intersection **hashNameMap, **hashCoordMap;
};