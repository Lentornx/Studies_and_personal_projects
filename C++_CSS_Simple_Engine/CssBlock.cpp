#include "CssBlock.h"

CssBlock::CssBlock(AttributeRoot* Attributes, SelectorRoot* Selectors) {
	Sections[0] = new Css(Attributes, Selectors);
}

int CssBlock::GetCounter() {
	return counter;
}

void CssBlock::ChangeCounter(int num) {
	counter += num;
}

CssBlock* CssBlock::GetNext() {
	return next;
}

void CssBlock::SetNext(CssBlock* newNext) {
	this->next = newNext;
}

CssBlock* CssBlock::GetPrev() {
	return prev;
}

void CssBlock::SetPrev(CssBlock* prev) {
	this->prev = prev;
}

void CssBlock::SetSection(int i, AttributeRoot* Attributes, SelectorRoot* Selectors) {
	Sections[i] = new Css(Attributes, Selectors);
}

void CssBlock::SetSection(int i, Css* null) {
	Sections[i] = null;
}

Css* CssBlock::GetSection(int i) {
	return Sections[i];
}

CssBlock::~CssBlock() {
	for (int i = 0; i < T; i++) {
		if (Sections[i] != nullptr)
		{
			delete Sections[i];
		}
	}
}