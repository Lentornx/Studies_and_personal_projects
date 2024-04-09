#pragma once
#include "Css.h"
class CssBlock {
	CssBlock *next = nullptr, *prev = nullptr;
	Css* Sections[T]={nullptr};
	int counter = 1;

public:
	CssBlock(AttributeRoot* Attributes, SelectorRoot* Selectors);

	CssBlock* GetNext();
	void SetNext(CssBlock* newNext);

	CssBlock* GetPrev();
	void SetPrev(CssBlock* prev);

	int GetCounter();
	void ChangeCounter(int num);

	void SetSection(int i, AttributeRoot* Attributes, SelectorRoot* Selectors);
	void SetSection(int i, Css* null);
	Css* GetSection(int i);

	~CssBlock();
};