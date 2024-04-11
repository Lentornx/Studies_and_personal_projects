#include "Organism.h"

Organism::Organism(int x, int y, World& world)
	: xPos(x), yPos(y), world(world) {}

Organism::Organism(int str, int ini, int xPos, int yPos, int age, int oId, bool moved, World& world)
	:str(str), ini(ini), xPos(xPos), yPos(yPos), age(age), oId(oId), moved(moved), world(world) {}

int Organism::GetS() const {
	return str;
}
void Organism::SetS(int strength) {
	this->str = strength;
}
int Organism::GetI() const {
	return ini;
}
void Organism::SetI(int initiative) {
	this->ini = initiative;
}
int Organism::GetX() const {
	return xPos;
}
void Organism::SetX(int xPos) {
	this->xPos = xPos;
}
int Organism::GetY() const {
	return yPos;
}
void Organism::SetY(int yPos) {
	this->yPos = yPos;
}
World& Organism::GetW() const {
	return world;
}
int Organism::GetSId() const {
	return speciesId;
}
int Organism::GetOId() const {
	return oId;
}
void Organism::SetOId(int oId) {
	this->oId = oId;
}
int Organism::GetAge() const {
	return age;
}
void Organism::SetAge(int age) {
	this->age = age;
}
bool Organism::HasMoved() {
	return moved;
}
void Organism::SetHasMoved(bool moved) {
	this->moved = moved;
}
string Organism::GetName() {
	return name;
}
Organism::~Organism() {
}