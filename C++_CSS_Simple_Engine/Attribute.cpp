#include "Attribute.h"

Attribute::Attribute(char* value, char* property)
: value(value), property(property) {

}

char* Attribute::GetValue() {
	return value;
}

void Attribute::SetValue(char* value) {
	this->value = value;
}

char* Attribute::GetProperty() {
	return property;
}

bool Attribute::CompareProperty(char* property) {
	int i = 0;
	while (this->property[i] != '\0' && property[i] != '\0')
	{
		if (this->property[i] != property[i])
			return false;
		i++;
	}
	if (this->property[i] == '\0' && property[i] == '\0')
		return true;
	else
		return false;
}

Attribute* Attribute::GetNext() {
	return next;
}
void Attribute::SetNext(Attribute* next) {
	this->next = next;
}

Attribute::~Attribute() {

}