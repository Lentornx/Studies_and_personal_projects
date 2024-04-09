#pragma once
#include "Point.h"
class PointQueue
{
public:
	PointQueue();

	void Add(int x, int y);
	Point* GetLast();
	bool IsEmpty();

	~PointQueue();

private:
	Point *head = nullptr, *tail = nullptr;
};