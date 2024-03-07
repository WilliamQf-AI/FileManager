#pragma once
#include "ToolBarInputBase.h"

class TitleBarTab;
class ToolBarAddress:public ToolBarInputBase
{
public:
	ToolBarAddress(WindowMain* root);
	~ToolBarAddress();
	void tabChange(TitleBarTab* tab, TitleBarTab* tabNew);
private:
	void resize(const int& w, const int& h) override;
	void paint2(SkCanvas* canvas) override;
};

