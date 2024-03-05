#pragma once
#include "ControlBase.h"

class ToolBarSearch :public ControlBase
{
public:
	ToolBarSearch(WindowMain* root);
	~ToolBarSearch();
private:
	void resize(const int& w, const int& h) override;
	void paint(SkCanvas* canvas) override;
	void mouseDown(const int& x, const int& y) override;
};

