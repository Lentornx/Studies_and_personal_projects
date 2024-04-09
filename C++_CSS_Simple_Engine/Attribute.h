#pragma once
#include "Defines.h"
#include <iostream>
using namespace std;

class Attribute {
	char *value, *property;
	Attribute* next = nullptr;

public:
	Attribute(char* value, char* property);

	char* GetValue();
	void SetValue(char* value);

	char* GetProperty();
	bool CompareProperty(char* property);

	Attribute* GetNext();
	void SetNext(Attribute* next);

	~Attribute();
};