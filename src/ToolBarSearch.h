#pragma once
#include "ToolBarInputBase.h"

class ToolBarSearch :public ToolBarInputBase
{
public:
	ToolBarSearch(WindowMain* root);
	~ToolBarSearch();
private:
	void resize(const int& w, const int& h) override;
	void paint2(SkCanvas* canvas) override;
};

