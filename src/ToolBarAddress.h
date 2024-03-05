#pragma once
#include "ControlBase.h"

class ToolBarAddress:public ControlBase
{
public:
	ToolBarAddress(WindowMain* root);
	~ToolBarAddress();
private:
	void resize(const int& w, const int& h) override;
	void paint(SkCanvas* canvas) override;
	void mouseDown(const int& x, const int& y) override;
	bool isFocus{ false };
};

