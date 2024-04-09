#pragma once
class Point
{
public:
	Point(int x, int y, Point* next);

	Point* GetNext();
	int GetX();
	int GetY();

	void SetNext(Point* next);

	~Point();

private:
	int x, y;
	Point* next;
};
