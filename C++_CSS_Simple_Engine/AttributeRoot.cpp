#include "AttributeRoot.h"

AttributeRoot::AttributeRoot() {
}

Attribute* AttributeRoot::GetFirst() {
	return first;
}

void AttributeRoot::AddLast(char* value, char* property) {
	
	if (first == nullptr) 
	{
		Attribute* newAttr = new Attribute(value, property);
		first = newAttr;
	}
	else
	{
		Attribute* i = first;
		while (!(i->CompareProperty(property)))
		{
			if (i->GetNext() != nullptr)
				i = i->GetNext();
			else 
				break;
		}
		if (!(i->CompareProperty(property)))
		{
			Attribute* newAttr = new Attribute(value, property);
			i->SetNext(newAttr);
		}
		else
		{
			i->SetValue(value);
		}
	}
}

void AttributeRoot::Rm(char* property) {
	if (first != nullptr)
	{
		Attribute* i = first;
		Attribute* tmp = i;
		bool found = false;
		while (true)
		{
			if (i->CompareProperty(property))
			{
				found = true;
				break;
			}
			if (i->GetNext() != nullptr)
			{
				tmp = i;
				i = i->GetNext();
			}
			else
				break;
		}
		if (found)
		{
			if (i != first)
			{
				if (i->GetNext() == nullptr)
					tmp->SetNext(nullptr);
				else
				 	tmp->SetNext(i->GetNext());
			}
			else
			{
				if (i->GetNext() == nullptr)
					first = nullptr;
				else
					first = i->GetNext();
			}
			delete i;
		}
	}
}

char* AttributeRoot::Search(char* property)
{
	if (first != nullptr)
	{
		Attribute* i = first;
		while (true)
		{
			if (i->CompareProperty(property))
			{
				return i->GetValue();
			}
			if (i->GetNext() != nullptr)
				i = i->GetNext();
			else
				break;
		}
	}
	return NULL;
}

int AttributeRoot::Count() {

	if (first == nullptr)
		return 0;
	else
	{
		int c = 1;
		Attribute* i = first;
		while (i->GetNext() != nullptr)
		{
			c++;
			i = i->GetNext();
		}
		return c;
	}
}

char* AttributeRoot::ViewSingle(char* n) {
	if (first != nullptr)
	{
		Attribute* i = first;
		while (true)
		{
			if (i->CompareProperty(n))
			{
				return i->GetValue();
			}
			if (i->GetNext() != nullptr)
				i = i->GetNext();
			else
				break;
		}
	}
	return NULL;
}

void AttributeRoot::View() {
	if (first == nullptr)
		cout << " empty ";
	else
	{
		Attribute* i = first;
		cout << "{";
		while (i->GetNext() != nullptr)
		{
			cout << i->GetProperty() << " : " << i->GetValue() << "; ";
			i = i->GetNext();
		}
		cout << i->GetProperty() << " : " << i->GetValue() << "}" << endl;
	}
}

AttributeRoot::~AttributeRoot() {
	if (first != nullptr)
	{
		Attribute* tmp = first;
		while (tmp->GetNext() != nullptr) {
			Attribute* toBeDel = tmp;
			tmp = tmp->GetNext();
			delete toBeDel;
		}
		delete tmp;
	}
}