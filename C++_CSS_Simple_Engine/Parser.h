#pragma once
#include "CssRoot.h"
class Parser
{
public:
	Parser();
	void Parse(char Command);
	~Parser();

private:
	char buffer[BUFFER_SIZE];
	bool commandsActive = false, arg1IsNum = false, arg3IsNum = false, selInputOver = false;
	int argNum = 1, charSize = 0, iArg, jArg;
	char* tmpSel = nullptr, * tmpProp = nullptr, * tmpVal = nullptr, * arg1 = nullptr, arg2, * arg3 = nullptr;
	CssRoot* Sections = new CssRoot();
	SelectorRoot* sel = new SelectorRoot();
	AttributeRoot* attr = new AttributeRoot();
};