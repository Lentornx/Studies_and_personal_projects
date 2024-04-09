#include "Map.h"

Map::Map()
{
	cin >> w >> h;
	layout = new char* [h];
	pathMarker = new int* [h];
	for (int y = 0; y < h; y++)
	{
		layout[y] = new char[w];
		pathMarker[y] = new int[w];
	}
	pointX = new int[w * h];
	pointY = new int[w * h];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
		{
			cin >> layout[y][x];
			if (layout[y][x] == '*')
			{
				pointX[cityCount] = x;
				pointY[cityCount] = y;
				cityCount++;
			}
		}
}

void Map::ParseHashMap()
{
	hashNameMap = new Intersection*[cityCount * 2];
	for (int i = 0; i < cityCount * 2; i++) {
		hashNameMap[i] = nullptr; 
	}
	hashCoordMap = new Intersection*[cityCount * 2];
	for (int i = 0; i < cityCount * 2; i++) {
		hashCoordMap[i] = nullptr;
	}

	Intersection* tmp;
	for (int i = 0; i < cityCount; i++)
	{
		char* name = ParseCityName(pointX[i], pointY[i]);
		tmp = new Intersection(name, pointX[i], pointY[i]);
		AddToHashMap(tmp);
	}
}

char* Map::ParseCityName(int x, int y) 
{
	for(int i = -1; i <= 1; i++)
		for (int i2 = -1; i2 <= 1; i2++)
			if(y + i >= 0 && x + i2 >= 0  && y + i < h && x + i2 < w)
				if (layout[y + i][x + i2] != '*' && layout[y + i][x + i2] != '#' 
					&& layout[y + i][x + i2] != '.' && layout[y + i][x + i2] != '@') {
					y += i;
					x += i2;
				}
	while (x - 1 >= 0 && layout[y][x - 1] != '*' && layout[y][x - 1] != '#'
		&& layout[y][x - 1] != '.' && layout[y][x - 1] != '@')
		x--;

	char buffer[BUFFERSIZE];
	int nameSize = 0;

	while (true)
	{
		buffer[nameSize] = layout[y][x];
		nameSize++;
		if (x + 1 < w && layout[y][x + 1] != '*' && layout[y][x + 1] != '#'
			&& layout[y][x + 1] != '.' && layout[y][x + 1] != '@')
			x++;
		else
			break;
	}
	char* name = new char[nameSize+1];

	for (int i = 0; i < nameSize; i++)
		name[i] = buffer[i];

	name[nameSize] = '\0';
	return name;
}

int Map::CoordToHash(int x, int y) {
	return (x * 11 + y * 43) % cityCount * 2;
}

int Map::NameToHash(char* name) {
	return (name[0] * 11 + name[1] * 43) % cityCount * 2;
}

Intersection* Map::LookByCoord(int x, int y) {
	int i = CoordToHash(x, y);
	while (true) 
	{
		if(hashCoordMap[i] != nullptr && hashCoordMap[i]->GetX() == x && hashCoordMap[i]->GetY() == y)
			return hashCoordMap[i];
		else if (i < cityCount * 2 - 1)
			i++;
		else i = 0;
	}
}

Intersection* Map::LookByName(char* name) {
	int i = NameToHash(name);
	while (true)
	{
		if (hashNameMap[i] != nullptr && hashNameMap[i]->CompareName(name) == true)
			return hashNameMap[i];
		else if (i < cityCount * 2 - 1)
			i++;
		else i = 0;
	}
}

void Map::AddToHashMap(Intersection* tmp) 
{
	if(tmp->GetName() != nullptr)
	{
		int nameCode = NameToHash(tmp->GetName());
		while (hashNameMap[nameCode] != nullptr)
		{
			if (nameCode < cityCount * 2)
				nameCode++;
			else nameCode = 0;
		}
		hashNameMap[nameCode] = tmp;
	}
	int coordCode = CoordToHash(tmp->GetX(), tmp->GetY());
	while (hashCoordMap[coordCode] != nullptr)
	{
		if (coordCode < cityCount * 2)
			coordCode++;
		else coordCode = 0;
	}
	hashCoordMap[coordCode] = tmp;
}

char* Map::GetInput() {
	int i = 0;
	char buffer[BUFFERSIZE], input = 0;
	while (true)
	{
		cin.get(input);
		if (input <= 32)
		{
			if (i > 0)
				break;
		}
		else
		{
			buffer[i] = input;
			i++;
		}
	}
	char* result = new char[i + 1];
	for (int i2 = 0; i2 < i; i2++)
		result[i2] = buffer[i2];
	result[i] = '\0';
	return result;
}

void Map::ParseGraph() {
	for (int j = 0; j < cityCount * 2; j++)
		if (hashNameMap[j] != nullptr)
		{
			Intersection* In = hashNameMap[j];
			PointQueue Q = PointQueue();
			Q.Add(In->GetX(), In->GetY());
			for(int y = 0; y < h; y++)
				for (int x = 0; x < w; x++)
					pathMarker[y][x] = -1;
			pathMarker[In->GetY()][In->GetX()] = 0;
			Point* point;
			while (!Q.IsEmpty())
			{
				point = Q.GetLast();
				int x = point->GetX();
				int y = point->GetY();

				for (int changeX = -1; changeX <= 1; changeX++)
					for (int changeY = -1; changeY <= 1; changeY++)
						if ((changeX == 0 && changeY != 0) || (changeY == 0 && changeX != 0))
							if (y + changeY >= 0 && x + changeX >= 0 && y + changeY < h && x + changeX < w
								&& pathMarker[y + changeY][x + changeX] == -1)
							{
								if (layout[y + changeY][x + changeX] == '#')
								{
									pathMarker[y + changeY][x + changeX] = pathMarker[y][x] + 1;
									Q.Add(x + changeX, y + changeY);
								}
								else if (layout[y + changeY][x + changeX] == '*')
								{
									pathMarker[y + changeY][x + changeX] = pathMarker[y][x] + 1;
									CoordToHash(x + changeX, y + changeY);
									Intersection* neighbour = LookByCoord(x + changeX, y + changeY);
									In->addDest(neighbour, pathMarker[y + changeY][x + changeX]);
									neighbour->addDest(In, pathMarker[y + changeY][x + changeX]);
								}
							}
				delete point;
			}
		}

	int k, length = 0;
	char* source, * dest;
	char buffer[BUFFERSIZE], input;
	cin >> k;
	for (int i = 0; i < k; i++) {
		source = GetInput();
		dest = GetInput();
		cin >> length;
		Intersection* d = LookByName(dest);
		Intersection* s = LookByName(source);
		s->addDest(d, length);
		delete source;
		delete dest;
	}
}

void Map::Dijkstra(Intersection* source, char* dest, bool showPath)
{
	for (int i = 0; i < cityCount * 2; i++)
	{
		if(hashCoordMap[i] != nullptr)
		{
			hashCoordMap[i]->SetDist(BIG_NUMBER);
			hashCoordMap[i]->SetPrev(nullptr);
			hashCoordMap[i]->SetVisited(false);
		}
	}
	source->SetDist(0);
	Intersection* nextToVisit;
	while(true)
	{
		int min = BIG_NUMBER;
		nextToVisit = nullptr;
		for (int i = 0; i < cityCount * 2; i++)
		{
			if (hashCoordMap[i] != nullptr)
			{
				if (!hashCoordMap[i]->WasVisited() && hashCoordMap[i]->GetDist() < min)
				{
					nextToVisit = hashCoordMap[i];
					min = hashCoordMap[i]->GetDist();
				}
			}
		}
		if (nextToVisit->CompareName(dest))
			break;
		nextToVisit->MeasureNeighbours();
		nextToVisit->SetVisited(true);
	}
	cout << nextToVisit->GetDist();
	if(nextToVisit->GetPrev() != nullptr)
		nextToVisit = nextToVisit->GetPrev();
	if (showPath)
	{
		OutputPath(nextToVisit);
	}
	cout << endl;
}

void Map::OutputPath(Intersection* currentI)
{
	if (currentI->GetPrev() != nullptr)
	{
		OutputPath(currentI->GetPrev());
		if (currentI->GetName() != nullptr)
			cout << " " << currentI->GetName();
	}
}

Map::~Map()
{
	for (int y = 0; y < h; y++)
	{
		delete layout[y];
		delete pathMarker[y];
	}
	for (int i = 0; i < cityCount * 2; i++)
	{
		delete hashNameMap[i];
	}
	delete[] layout;
	delete[] pathMarker;
	delete[] hashNameMap;
	delete[] hashCoordMap;
}
