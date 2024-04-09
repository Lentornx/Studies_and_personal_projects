#include "Selector.h"

Selector::Selector(char* data) : data(data) {

}

char* Selector::GetData() {
	return data;
}

bool Selector::CompareData(char* data) {
	int i = 0;
	while (this->data[i] != '\0' && data[i] != '\0')
	{
		if (this->data[i] != data[i])
			return false;
		i++;
	}
	if (this->data[i] == '\0' && data[i] == '\0')
		return true;
	else 
		return false;
}

Selector* Selector::GetNext() {
	return next;
}
void Selector::SetNext(Selector* next) {
	this->next = next;
}

Selector::~Selector() {

}