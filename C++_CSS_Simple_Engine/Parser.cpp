#include "Parser.h"

Parser::Parser() {

}

void Parser::Parse(char command) {
	if (!commandsActive)
	{
		if (command >= 'a' && command <= 'z')
		{
			buffer[charSize] = command;
			charSize++;
		}
		else if ((command == ',' && !selInputOver) || command == '{')
		{
			if (charSize > 0)
			{
				charSize--;
				while (buffer[charSize] == ' ')
				{
					buffer[charSize] = '\0';
					charSize--;
				}
				charSize++;
				tmpSel = new char[charSize + 1];
				for (int i = 0; i < charSize; i++)
				{
					tmpSel[i] = buffer[i];
				}
				tmpSel[charSize] = '\0';
				sel->AddLast(tmpSel);
				charSize = 0;
			}
			if (command == '{')
				selInputOver = true;
		}
		else if (command == ':' && selInputOver)
		{
			if (charSize > 0)
			{
				charSize--;
				while (buffer[charSize] == ' ')
				{
					buffer[charSize] = '\0';
					charSize--;
				}
				charSize++;
				tmpProp = new char[charSize + 1];
				for (int i = 0; i < charSize; i++)
				{
					tmpProp[i] = buffer[i];
				}
				tmpProp[charSize] = '\0';
				charSize = 0;
			}
		}
		else if ((command == ';' && selInputOver) || command == '}')
		{
			if (charSize > 0)
			{
				charSize--;
				while (buffer[charSize] == ' ')
				{
					buffer[charSize] = '\0';
					charSize--;
				}
				charSize++;
				tmpVal = new char[charSize + 1];
				for (int i = 0; i < charSize; i++)
				{
					tmpVal[i] = buffer[i];
				}
				tmpVal[charSize] = '\0';
				charSize = 0;
				attr->AddLast(tmpVal, tmpProp);
			}
			if (command == '}')
			{
				Sections->AddLast(attr, sel);
				sel = new SelectorRoot();
				attr = new AttributeRoot();
				selInputOver = false;
			}
		}
		else if (command == '?')
		{
			cin >> command >> command >> command;
			commandsActive = true;
		}
		else if (command == ' ')
		{
			if (charSize > 0)
			{
				buffer[charSize] = command;
				charSize++;
			}
		}
		else if (command >= 32)
		{
			buffer[charSize] = command;
			charSize++;
		}
	}
	else
	{
		if (command >= '1' && command <= '9' && charSize == 0) {
			int tmp = 0;
			while (command != ',' && command != '\n') {
				tmp = 10 * tmp + command - 48;
				cin.get(command);
			}
			if (argNum == 1)
			{
				iArg = tmp;
				arg1IsNum = true;
			}
			else if (argNum == 3)
			{
				jArg = tmp;
				arg3IsNum = true;
			}
			argNum++;
		}
		else if (argNum == 2)
		{
			arg2 = command;
			cin >> command; //zaczytanie przecinka
			argNum++;
		}
		else if (command == '*')
		{
			if (argNum == 1)
			{
				cin >> command >> command >> command;
				commandsActive = false;
			}
			else
			{
				buffer[charSize] = command;
				charSize++;
			}
		}
		else if (command == '?')
		{
			if (argNum == 1) {
				cout << "? == " << Sections->GetCounter() << endl;
			}
			else
			{
				buffer[charSize] = command;
				charSize++;
			}
		}
		else if (command == ',' || (command == '\n' && argNum == 3))
		{
			char* tmp = new char[charSize + 1];
			for (int i = 0; i < charSize; i++)
			{
				tmp[i] = buffer[i];
			}
			tmp[charSize] = '\0';
			if (argNum == 1)
				arg1 = tmp;
			else
				arg3 = tmp;
			tmp = nullptr;
			delete[] tmp;
			argNum++;
			charSize = 0;
		}
		else if (command == ' ')
		{
			if (charSize > 0)
			{
				buffer[charSize] = command;
				charSize++;
			}
		}
		else if (command != '\n')
		{
			buffer[charSize] = command;
			charSize++;
		}
		if (command == '\n')
		{
			if (argNum > 3 && (arg2 == 'S' || arg2 == 'A' || arg2 == 'D' || arg2 == 'E'))
			{

				if (arg2 == 'D')
					Sections->Rm(iArg - 1, arg3);
				else if (arg3[0] == '?')
				{
					if (arg1IsNum)
						Sections->CountElements(iArg - 1, arg2);
					else
						Sections->CountElementAppearences(arg1, arg2);
				}
				else if (arg3IsNum)
					Sections->ViewSingleSel(iArg - 1, jArg);
				else if (arg2 == 'E')
					Sections->E(arg1, arg3);
				else
					Sections->ViewSingleAttr(iArg - 1, arg3);
			}
			argNum = 1;
			arg1IsNum = false;
			arg3IsNum = false;
			if (arg3 != nullptr)
				arg3[0] = '/0';
			if (arg1 != nullptr)
				arg1[0] = '/0';
			charSize = 0;
		}
	}
}

Parser::~Parser() {
	delete Sections;
	delete attr;
	delete sel;
	delete[] tmpVal;
	delete[] tmpProp;
	delete[] tmpSel;
	delete[] arg1;
	delete[] arg3;
}