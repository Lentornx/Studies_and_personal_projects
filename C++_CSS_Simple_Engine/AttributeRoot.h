#pragma once
#include "Attribute.h"

class AttributeRoot {
	Attribute* first = nullptr;

public:
	AttributeRoot();

	Attribute* GetFirst();
	void SetFirst(Attribute* next);
	void AddLast(char* value, char* property);
	void Rm(char* property);
	char* Search(char* n);
	int Count();
	char* ViewSingle(char* n);
	void View();

	~AttributeRoot();
};