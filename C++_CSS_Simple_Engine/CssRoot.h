#pragma once
#include "CssBlock.h"

class CssRoot {
	CssBlock* first = nullptr;
	int counter = 0, sectionsAdded = 0;
	

public:
	CssRoot();

	CssBlock* GetFirst();

	int GetCounter();
	void AddLast(AttributeRoot* newAttr, SelectorRoot* newSel);
	void Rm(int i, char* n);
	void RmBlock(int iB);
	void E(char* z, char* n);
	void CountElements(int i, char SelOrAttr);
	void CountElementAppearences(char* name, char SelOrAttr);
	void ViewSingleSel(int i, int j);
	void ViewSingleAttr(int i, char* n);

	~CssRoot();
};