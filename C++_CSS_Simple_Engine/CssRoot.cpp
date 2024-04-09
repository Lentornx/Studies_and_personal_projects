#include "CssRoot.h"

CssRoot::CssRoot() {

}
CssBlock* CssRoot::GetFirst() {
	return first;
}
int CssRoot::GetCounter() {
	return counter;
}

void CssRoot::AddLast(AttributeRoot* newAttr, SelectorRoot* newSel)
{
	int j;
	if (first == nullptr)
	{
		CssBlock* newBlock = new CssBlock(newAttr, newSel);
		first = newBlock;
		counter++;
		sectionsAdded++;
	}
	else
	{
		CssBlock* BlockI = first;
		int tmpCounter = sectionsAdded;
		while (tmpCounter >= T)
		{
			tmpCounter -= T;
			if (BlockI->GetNext() != nullptr)
				BlockI = BlockI->GetNext();
			else break;
		}
		if (tmpCounter == 0)
		{
			CssBlock* newBlock = new CssBlock(newAttr, newSel);
			BlockI->SetNext(newBlock);
			newBlock->SetPrev(BlockI);
		}
		else
		{
			BlockI->SetSection(tmpCounter, newAttr, newSel);
			BlockI->ChangeCounter(1);
		}
		counter++;
		sectionsAdded++;
	}
}

void CssRoot::RmBlock(int iB)
{
	CssBlock* i = first;
	CssBlock* tmp = i;
	bool found = false;
	while (true)
	{
		if (iB == 0)
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
			{
				tmp->SetNext(i->GetNext());
				i->GetNext()->SetPrev(tmp);
			}
		}
		else
		{
			if (i->GetNext() != nullptr)
			{
				first = i->GetNext();
				first->SetPrev(nullptr);
			}	
			else
				first = nullptr;
		}
		delete i;
		sectionsAdded -= T;
		if (sectionsAdded < 0)
			sectionsAdded = 0;
	}
}

void CssRoot::Rm(int i, char* n) {
	bool removeWhole = false;
	int j;
	if (first != nullptr && i <= counter)
	{
		CssBlock* BlockI = first;
		int tmpCounter = i;
		while (tmpCounter >= BlockI->GetCounter() && BlockI->GetNext() != nullptr)
		{
			tmpCounter -= BlockI->GetCounter();
			BlockI = BlockI->GetNext();
		}
		if (tmpCounter < T)
		{
			for (j = 0; tmpCounter >= 0 && j < T; j++)
			{
				if (BlockI->GetSection(j) != nullptr)
					tmpCounter--;
			}
			if (tmpCounter == -1)
			{
				tmpCounter = j - 1;
				if (n[0] != '*')
				{
					if (BlockI->GetSection(tmpCounter)->GetAttr()->Search(n))
					{
						BlockI->GetSection(tmpCounter)->GetAttr()->Rm(n);
						if (BlockI->GetSection(tmpCounter)->GetAttr()->GetFirst() == nullptr)
							removeWhole = true;
						cout << i + 1 << ",D," << n << " == deleted" << endl;
					}
				}
				if (n[0] == '*' || removeWhole)
				{
					counter--;
					BlockI->ChangeCounter(-1);
					delete BlockI->GetSection(tmpCounter);
					BlockI->SetSection(tmpCounter, nullptr);
					if (!removeWhole)
						cout << i + 1 << ",D,* == deleted" << endl;
				}
				if (BlockI->GetCounter() == 0)
				{
					RmBlock(i + 1 / T);
				}
			}
		}
	}
}

void CssRoot::E(char* z, char* n)
{
	if (first != nullptr)
	{
		bool found = false;
		CssBlock* BlockI = first;
		int tmpCounter = counter;
		while (tmpCounter >= BlockI->GetCounter() && BlockI->GetNext() != nullptr)
		{
			tmpCounter -= BlockI->GetCounter();
			BlockI = BlockI->GetNext();
		}
		while (!found)
		{
			for (int i = T - 1; i >= 0; i--)
			{
				if (BlockI->GetSection(i) != nullptr)
				{
					if (BlockI->GetSection(i)->GetSel()->Search(z) == true || BlockI->GetSection(i)->GetSel()->GetFirst() == nullptr)
					{
						if (BlockI->GetSection(i)->GetAttr()->Search(n) != NULL)
						{
							found = true;
							cout << z << ",E," << n << " == " << BlockI->GetSection(i)->GetAttr()->Search(n) << endl;
							break;
						}	
					}
				}
			}
			if (BlockI->GetPrev() == nullptr)
				break;
			else
				BlockI = BlockI->GetPrev();
		} 
	}
}

void CssRoot::CountElements(int i, char SelOrAttr) {
	if (first != nullptr && i+1 <= counter)
	{
		int tmpCounter = i;
		CssBlock* BlockI = first;
		int j;
		while (tmpCounter >= BlockI->GetCounter() && BlockI->GetNext() != nullptr)
		{
			tmpCounter -= BlockI->GetCounter();
			BlockI = BlockI->GetNext();
		}
		for (j = 0; tmpCounter >= 0 && j < T; j++)
		{
			if (BlockI->GetSection(j) != nullptr)
				tmpCounter--;
		}
		if (tmpCounter == -1)
		{
			tmpCounter = j - 1;
			if (SelOrAttr == 'A')
				cout << i + 1 << ',' << SelOrAttr << ",? == " << BlockI->GetSection(tmpCounter)->GetAttr()->Count() << endl;
			else
				cout << i + 1 << ',' << SelOrAttr << ",? == " << BlockI->GetSection(tmpCounter)->GetSel()->Count() << endl;
		}
	}
}

void CssRoot::CountElementAppearences(char* name, char SelOrAttr) {
	int c = 0;
	if (first != nullptr)
	{
		CssBlock* BlockI = first;
		while (true)
		{
			if (SelOrAttr == 'S')
			{
				for (int i = 0; i < T; i++)
				{
					if (BlockI->GetSection(i) != nullptr)
						if (BlockI->GetSection(i)->GetSel()->Search(name) != false)
							c++;
				}
			}
			else 
			{
				for (int i = 0; i < T; i++)
				{
					if (BlockI->GetSection(i) != nullptr)
						if (BlockI->GetSection(i)->GetAttr()->Search(name) != NULL)
							c++;
				}
			}
			if (BlockI->GetNext() != nullptr)
				BlockI = BlockI->GetNext();
			else
				break;
		}
	}
		cout << name << ',' << SelOrAttr << ",? == " << c << endl;
}

void CssRoot::ViewSingleSel(int i, int j) {
	if (first != nullptr && i+1 <= counter)
	{
		int tmpCounter = i;
		int c;
		CssBlock* BlockI = first;
		while (tmpCounter >= BlockI->GetCounter() && BlockI->GetNext() != nullptr)
		{
			tmpCounter -= BlockI->GetCounter();
			BlockI = BlockI->GetNext();
		}
		for (c = 0; tmpCounter >= 0 && c < T; c++)
		{
			if (BlockI->GetSection(c) != nullptr)
				tmpCounter--;
		}
		if (tmpCounter == -1)
		{
			tmpCounter = c - 1;
			if (BlockI->GetSection(tmpCounter)->GetSel()->ViewSingle(j)) {
				cout << i + 1 << ",S," << j << " == " << BlockI->GetSection(tmpCounter)->GetSel()->ViewSingle(j) << endl;
			}
		}
	}
}

void CssRoot::ViewSingleAttr(int i, char* n) {
	if (first != nullptr)
	{
		int j, tmpCounter = i;
		CssBlock* BlockI = first;
		while (tmpCounter >= BlockI->GetCounter() && BlockI->GetNext() != nullptr)
		{
			tmpCounter -= BlockI->GetCounter();
			BlockI = BlockI->GetNext();
		}
		for (j = 0; tmpCounter >= 0 && j < T; j++)
		{
			if (BlockI->GetSection(j) != nullptr)
				tmpCounter--;
		}
		if (tmpCounter == -1)
		{
			tmpCounter = j - 1;
			if (BlockI->GetSection(tmpCounter)->GetAttr()->ViewSingle(n)) {
				cout << i + 1 << ",A," << n << " == " << BlockI->GetSection(tmpCounter)->GetAttr()->ViewSingle(n) << endl;
			}
		}
	}
}

CssRoot::~CssRoot() {
	if (first != nullptr)
	{
		CssBlock* tmp = first;
		while (tmp->GetNext() != nullptr) {
			CssBlock* toBeDel = tmp;
			tmp = tmp->GetNext();
			delete toBeDel;
		}
		delete tmp;
	}
}