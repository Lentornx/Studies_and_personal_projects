#include "Css.h"

Css::Css() {

}

Css::Css(AttributeRoot* Attributes, SelectorRoot* Selectors) 
	: Attributes(Attributes), Selectors(Selectors) {
}

AttributeRoot* Css::GetAttr() {
	return Attributes;
}

void Css::SetAttr(AttributeRoot* Attributes) {
	this->Attributes = Attributes;
}

SelectorRoot* Css::GetSel() {	
	return Selectors;
}

void Css::View() {
	Selectors->View();
	Attributes->View();
}

Css::~Css() {
	if (Selectors->GetFirst() != nullptr)
		delete Selectors;
	delete Attributes;
}