#include "SelectorRoot.h"

SelectorRoot::SelectorRoot() {
}

Selector* SelectorRoot::GetFirst() {
	return first;
}

void SelectorRoot::AddLast(char* data) 
{
	Selector* newSel = new Selector(data);
	if (first == nullptr)
	{
		first = newSel;
	}
	else
	{
		Selector* i = first;
		while (i->GetNext() != nullptr)
		{
			i = i->GetNext();
		}
		i->SetNext(newSel);
	}	
}

bool SelectorRoot::Search(char* data) 
{
	if (first != nullptr)
	{
		Selector* i = first;
		while (true)
		{
			if (i->CompareData(data))
			{
				return true;
			}
			if (i->GetNext() != nullptr)
				i = i->GetNext();
			else break;
		}
	}	
	return false;
}

int SelectorRoot::Count() {
	if (first == nullptr)
		return 0;
	else
	{
		int c = 1;
		Selector* i = first;
		while (i->GetNext() != nullptr)
		{
			c++;
			i = i->GetNext();
		}
		return c;
	}
}

char* SelectorRoot::ViewSingle(int j) {
	if (first != nullptr)
	{
		int tmpJ = 1;
		Selector* i = first;
		while (tmpJ++)
		{
			if (tmpJ-1 == j)
			{
				return i->GetData();
			}
			if (i->GetNext() != nullptr)
				i = i->GetNext();
			else
				break;
		}
	}
	return NULL;
}

void SelectorRoot::View() {
	
	if (first == nullptr)
		cout << "no selectors ";
	else
	{
		Selector* i = first;
		while (i->GetNext() != nullptr)
		{
			cout << i->GetData() << ", ";
			i = i->GetNext();
		}
		cout << i->GetData() << " ";
	}
}

SelectorRoot::~SelectorRoot() {
	if (first != nullptr)
	{
		Selector* tmp = first;
		while (tmp->GetNext() != nullptr) {
			Selector* toBeDel = tmp;
			tmp = tmp->GetNext();
			delete toBeDel;
		}
		delete tmp;
	}
}