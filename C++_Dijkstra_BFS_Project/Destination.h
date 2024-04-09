#pragma once
class Intersection;
class Destination
{
public:
	Destination(Intersection* dest, int length);

	Intersection* GetDestination();
	int GetLength();
	Destination* GetNext();

	void SetNext(Destination* newDest);

	~Destination();

private:
	Destination* next = nullptr;
	Intersection* dest;
	int length;
};