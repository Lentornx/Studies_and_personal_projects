#pragma once
#include "Defines.h"
#include <iostream>
using namespace std;

class Selector {
	char* data;
	Selector* next = nullptr;

public:
	Selector(char* data);

	char* GetData();
	bool CompareData(char* data);

	Selector* GetNext();
	void SetNext(Selector* next);

	~Selector();
};