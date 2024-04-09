#pragma once
#include "AttributeRoot.h"
#include "SelectorRoot.h"

class Css {
	AttributeRoot* Attributes = nullptr;
	SelectorRoot* Selectors = nullptr;

public:
	Css();
	Css(AttributeRoot* Attributes, SelectorRoot* Selectors);
	AttributeRoot* GetAttr();
	void SetAttr(AttributeRoot* Attributes);

	SelectorRoot* GetSel();

	void View();

	~Css();
};