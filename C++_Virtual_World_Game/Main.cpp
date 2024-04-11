#include "World.h"
int main()
{
	int width, height;
	cout << "podaj szerokosc mapy" << endl;
	cin >> width;
	system("CLS");
	cout << "podaj wysokosc mapy" << endl;
	cin >> height;
	system("CLS");
	World world(height, width);
	world.StartGame();
	while (world.PlayerAlive())
	{
		system("CLS");
		world.ResolveTurn();
		cout << "press t to proceed to new turn" << endl;
		char input = 0;

		while(input != 't')
			input = _getch();
	}
	cout << endl << "GAME OVER" << endl;
	return 0;
}
