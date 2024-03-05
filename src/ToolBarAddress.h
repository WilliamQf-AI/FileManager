#pragma once
#include "ToolBarInputBase.h"

class ToolBarAddress:public ToolBarInputBase
{
public:
	ToolBarAddress(WindowMain* root);
	~ToolBarAddress();
private:
	void resize(const int& w, const int& h) override;
	void paint2(SkCanvas* canvas) override;
};

