#include "Includes.h"

World::World(int height, int width) 
: height(height), width(width) {
	organisms = new Organism*[height*width];
	for (int i = 0; i < height * width; i++) {
		organisms[i] = nullptr;
	}
	map = new char*[height];
	for (int i = 0; i < height; i++) {
		map[i] = new char[width];
	}
}

int World::GetH() const {
	return height;
}
int World::GetW() const {
	return width;
}
void World::SetH(int h) {
	height = h;
}
void World:: SetW(int w) {
	width = w;
}

void World::SetMap(int x, int y, char sign) {
	map[y][x] = sign;
}

bool World::PlayerAlive() {
	if (player != nullptr)
		return true;
	return false;
}

void World::AddOrganism(Organism* newOrganism) {
	organisms[organismCount] = newOrganism;
	organisms[organismCount]->SetOId(organismCount);
	organismCount++;
}

void World::RmOrganism(int id) {
	if (player == organisms[id])
		player = nullptr;
	Organism* tmp =  organisms[id];
	organisms[id] = nullptr;
	delete tmp;
}

void World::StartGame() {

	player = new Human(width / 2, height / 2, *this);
	AddOrganism(player);
	int toBeAdded, rX, rY;
	toBeAdded = 1 + (height * width / 60);
	for (int i = 0; i < toBeAdded; i++) {
		for (int i2 = 0; i2 < 15; i2++) {
			while (true) {
				rX = rand() % width;
				rY = rand() % height;
				if (LookForCollision(rX, rY) == nullptr) {
					if(i2 < 3)
						organisms[organismCount] = new Sheep(rX, rY, *this);
					else if (i2 < 4)
						organisms[organismCount] = new Wolf(rX, rY, *this);
					else if (i2 < 6)
						organisms[organismCount] = new Fox(rX, rY, *this);
					else if (i2 < 8)
						organisms[organismCount] = new Turtle(rX, rY, *this);
					else if (i2 < 10)
						organisms[organismCount] = new Antelope(rX, rY, *this);
					else if (i2 < 11)
						organisms[organismCount] = new Grass(rX, rY, *this);
					else if (i2 < 12)
						organisms[organismCount] = new Guarana(rX, rY, *this);
					else if (i2 < 13)
						organisms[organismCount] = new Dandelion(rX, rY, *this);
					else if (i2 < 14)
						organisms[organismCount] = new Wolfberry(rX, rY, *this);
					else
						organisms[organismCount] = new Hogweed(rX, rY, *this);
					organismCount++;
					break;
				}
			}
		}
	}
	ResolveTurn();
}

void World::sort() {
	int tmp = organismCount;
	for (int i = 0; i < tmp; i++)
	{
		if (organisms[i] == nullptr)
		{
			for (int i2 = tmp - 1; i2 > i; i2--)
			{
				if (organisms[i2] != nullptr)
				{
					organisms[i] = organisms[i2];
					organisms[i2] = nullptr;
					break;
				}
			}
		}
	}

	for (tmp = 0; organisms[tmp] != nullptr; tmp++) {}
	organismCount = tmp;
	

	for (int i = organismCount - 1; i > 0; i--) {
		for (int i2 = organismCount - 1; i2 > organismCount - 1 -i; i2--) 
		{
			if (organisms[i2]->GetI() > organisms[i2 - 1]->GetI()) {
				swap(organisms[i2], organisms[i2 - 1]);
			}
			else if (organisms[i2]->GetI() == organisms[i2 - 1]->GetI()) {
				if (organisms[i2]->GetAge() > organisms[i2 - 1]->GetAge())
					swap(organisms[i2], organisms[i2 - 1]);
			}
		}
	}

	for (int i = 0; i < organismCount; i++)
		organisms[i]->SetOId(i);
}

Organism* World::LookForCollision(int x, int y) {
	for (int i = 0; i < organismCount; i++) {
		if(organisms[i] != nullptr)
			if (organisms[i]->GetX() == x && organisms[i]->GetY() == y)
				return organisms[i];
	}
	return nullptr;
}

void World::ResolveTurn() {
	cout << "Virtual World Kamil Cwynar 193377" << endl
		<< "Legend:" << endl << "S - Sheep  W - Wol  F - Fox" << endl << "T - Turtle  A - Antelope  G - Grass" << endl
		<< "U - Guarana  D - Dandelion  B - Wolfberry" << endl << "H - Hogweed  Y - You(Human)" << endl
		<< "instructions:" << endl
		<< "wsad - moving around  f - special ability  o - save  l - load" << endl;
	char command = ' ';
	for (int i = 0; i < organismCount; i++) {
		if (organisms[i] != nullptr)
		{
			if (organisms[i] == player && !organisms[i]->HasMoved())
			{
				Print();
				while (!player->HasMoved())
				{
					command = _getch();
					system("CLS");
					if (command == 'o')
					{
						Save();
						system("CLS");
						Print();
					}
					else if (command == 'l')
					{
						Load();
						system("CLS");
						i = 0;
						break;
					}
					else
					{
						player->SetAction(command);
						player->TakeAction();
					}
				}
			}
			else if (command != 'l')
				organisms[i]->TakeAction();
			else 
				break;
		}
	}

	if (command != 'l')
	{
		sort();
		for (int i = 0; i < organismCount; i++) {
			if (organisms[i]->GetAge() == 0) {
				organisms[i]->SetAge(1);
			}
			organisms[i]->SetHasMoved(false);
		}
		Print();
	}
}

void World::Save() {
	string savefile;
	cout << "please name your savefile" << endl;
	cin >> savefile;
	ofstream write;
	write.open(savefile);
	write << width << " " << height << endl;
	int c = 0;
	for (int i = 0; i < organismCount; i++)
	{
		if (organisms[i] != nullptr)
		c++;
	}
	write << c << endl;
	for (int i = 0; i < organismCount; i++)
	{
		if (organisms[i] != nullptr)
		{
			write << organisms[i]->GetSId() << " " << organisms[i]->GetS() << " " << organisms[i]->GetI() << " " << organisms[i]->GetX() << " "
				<< organisms[i]->GetY() << " " << organisms[i]->GetAge() << " " << organisms[i]->GetOId() << " " << organisms[i]->HasMoved() << endl;
		}
	}
	write << player->GetCd() << " " << player->GetP();
	write.close();
}

void World::Load() {
	string savefile;
	cout << "please name savefile to load" << endl;
	cin >> savefile;
	ifstream read;
	read.open(savefile);
	read >> width >> height;
	organisms = new Organism * [height * width];
	for (int i = 0; i < height * width; i++) {
		organisms[i] = nullptr;
	}
	map = new char* [height];
	for (int i = 0; i < height; i++) {
		map[i] = new char[width];
	}
	read >> organismCount;
	int species, str, ini, x, y, age, oId, moved;
	for (int i = 0; i < organismCount; i++)
	{
		read >> species >> str >> ini >> x >> y >> age >> oId >> moved;
		if (species == 1)
			organisms[i] = new Sheep(str, ini, x, y, age, oId, moved, *this);
		else if (species == 2)
			organisms[i] = new Wolf(str, ini, x, y, age, oId, moved, *this);
		else if (species == 3)
			organisms[i] = new Fox(str, ini, x, y, age, oId, moved, *this);
		else if (species == 4)
			organisms[i] = new Turtle(str, ini, x, y, age, oId, moved, *this);
		else if (species == 5)
			organisms[i] = new Antelope(str, ini, x, y, age, oId, moved, *this);
		else if (species == 6)
			organisms[i] = new Grass(str, ini, x, y, age, oId, moved, *this);
		else if (species == 7)
			organisms[i] = new Guarana(str, ini, x, y, age, oId, moved, *this);
		else if (species == 8)
			organisms[i] = new Dandelion(str, ini, x, y, age, oId, moved, *this);
		else if (species == 9)
			organisms[i] = new Wolfberry(str, ini, x, y, age, oId, moved, *this);
		else if (species == 10)
			organisms[i] = new Hogweed(str, ini, x, y, age, oId, moved, *this);
		else
		{
			organisms[i] = new Human(str, ini, x, y, age, oId, moved, *this);
			player = (Human*)organisms[i];
		}
	}
	int cd, p;
	read >> cd >> p;
	player->SetCd(cd);
	player->SetP(p);
}

void World::Print() const {

	for (int i = 0; i < height; i++) {
		for (int i2 = 0; i2 < width; i2++) {
			 map[i][i2] = '.';
		}
	}
	for (int i = 0; i < organismCount; i++)
		if(organisms[i] != nullptr)
			organisms[i]->Print();

	for (int i = 0; i < height; i++) {
		for (int i2 = 0; i2 < width; i2++) {
				cout <<map[i][i2];
		}
		cout << endl;
	}
	cout << endl << "power left - " << player->GetP() << " cooldown - " << player->GetCd() << endl;
}

World::~World() 
{
	for (int i = 0; i < width*height; i++)
	{
		if(organisms[i] != nullptr)
		delete organisms[i];
	}
}