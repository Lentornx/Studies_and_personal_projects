#include "Intersection.h"

Destination::Destination(Intersection* dest, int length)
	:dest(dest), length(length) {}

Intersection* Destination::GetDestination() {
	return dest;
}
int Destination::GetLength() {
	return length;
}
Destination* Destination::GetNext() {
	return next;
}
void Destination::SetNext(Destination* newDest) {
	next = newDest;
}

Destination::~Destination() {

}
