#include "Map.h"
#include <fstream>
int main()
{
	ifstream file;
	file.open("file.txt");
	cin.rdbuf(file.rdbuf());
	Map map = Map();
	map.ParseHashMap();
	map.ParseGraph();
	int n; 
	cin >> n;
	char input;
	for (int i = 0; i < n; i++) {
		char* source = map.GetInput();
		char* dest = map.GetInput();
		bool showPath;
		cin >> showPath;
		Intersection* s = map.LookByName(source);
		map.Dijkstra(s, dest, showPath);
		delete source;
		delete dest;
	}
}