#pragma once
#include "Selector.h"

class SelectorRoot {
	Selector* first = nullptr;

public:

	SelectorRoot();

	Selector* GetFirst();
	void SetFirst(Selector* first);
	void AddLast(char* data);
	bool Search(char* data);
	int Count();
	char* ViewSingle(int j);
	void View();
	
	~SelectorRoot();
};