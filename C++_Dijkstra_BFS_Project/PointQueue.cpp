#include "PointQueue.h"

PointQueue::PointQueue() {

}

void PointQueue::Add(int x, int y) {
	Point* point;
	point = new Point(x, y, nullptr);
	if (tail != nullptr) {
		tail->SetNext(point);
	}
	else {
		head = point;
	}
	tail = point;
}

Point* PointQueue::GetLast() {
	if (head != nullptr)
	{
		Point* point;
		point = head;
		if(point->GetNext() != nullptr)
			head = point->GetNext();
		else {
			head = nullptr;
			tail = nullptr;
		}
		return point;
	}
	else return nullptr;
}

bool PointQueue::IsEmpty() {
	if (head != nullptr)
		return false;
	return true;
}

PointQueue::~PointQueue() {

}