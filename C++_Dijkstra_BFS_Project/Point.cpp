#include "Point.h"

Point::Point(int x, int y, Point* next) 
	:x(x), y(y), next(next) {}

Point* Point::GetNext() {
	return next;
}
int Point::GetX() {
	return x;
}
int Point::GetY() {
	return y;
}

void Point::SetNext(Point* next) {
	this->next = next;
}

Point::~Point() {

}