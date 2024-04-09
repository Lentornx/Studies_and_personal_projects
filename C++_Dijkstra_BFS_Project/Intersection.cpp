#include "Intersection.h"

Intersection::Intersection(char* name, int x, int y)
{
	this->x = x;
	this->y = y;
	this->name = name;
}

char* Intersection::GetName() {
	return name;
}
int Intersection::GetX() {
	return x;
}
int Intersection::GetY() {
	return y;
}

bool Intersection::WasVisited() {
	return visited;
}
Intersection* Intersection::GetPrev() {
	return prev;
}
int Intersection::GetDist() {
	return dist;
}

void Intersection::SetVisited(bool visited) {
	this->visited = visited;
}
void Intersection::SetPrev(Intersection* prev) {
	this->prev = prev;
}
void Intersection::SetDist(int dist) {
	this->dist = dist;
}

void Intersection::addDest(Intersection* dest, int length) {
	Destination* newDest = new Destination(dest, length);
	if (head == nullptr)
	{
		head = newDest;
	}
	else
	{
		Destination* i = head;
		while (i->GetNext() != nullptr)
		{
			i = i->GetNext();
		}
		i->SetNext(newDest);
	}
}

void Intersection::printNeighbours() {
	if (head != nullptr)
	{
		if (name != nullptr)
			cout << name << " ";
		cout << "(" << x << ", " << y << ") leads to ";
		Destination* i = head;
		while (true)
		{
			if (i->GetDestination()->GetName() != nullptr)
				cout << i->GetDestination()->GetName() << " ";
			cout << "(" << i->GetDestination()->GetX() << ", " << i->GetDestination()->GetY() << ") " << i->GetLength();
			if (i->GetNext() != nullptr)
			{
				cout << ", ";
				i = i->GetNext();
			}	
			else
				break;
		}
		cout << endl;
	}
}

void Intersection::MeasureNeighbours() {
	if (head != nullptr)
	{
		Destination* i = head;
		while (true)
		{
			int newLength = i->GetLength() + dist;
			if (i->GetDestination()->GetDist() > newLength)
			{
				i->GetDestination()->SetDist(newLength);
				i->GetDestination()->SetPrev(this);
			}
			if (i->GetNext() != nullptr)
				i = i->GetNext();
			else
				break;
		}
	}
}

bool Intersection::CompareName(char* tested) {
	if (tested != nullptr && this->name != nullptr)
	{
		int i = 0;
		while (this->name[i] != '\0' && tested[i] != '\0')
		{
			if (this->name[i] != tested[i])
				return false;
			i++;
		}
		if (this->name[i] == '\0' && tested[i] == '\0')
			return true;
		else
			return false;
	}
	else return false;
}

Intersection::~Intersection() 
{
	delete name;
	if(head != nullptr)
	{
		Destination* tmp = head;
		while (tmp->GetNext() != nullptr) {
			Destination* toBeDel = tmp;
			tmp = tmp->GetNext();
			delete toBeDel;
		}
		delete tmp;
	}

}