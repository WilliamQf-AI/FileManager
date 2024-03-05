#pragma once
#include "ControlBase.h"

class WindowMain;
class ToolBarInputBase :public ControlBase
{
public:
	ToolBarInputBase(WindowMain* root);
	~ToolBarInputBase();
	void paint(SkCanvas* canvas) override;
	virtual void paint2(SkCanvas* canvas) = 0;
	void mouseDown(const int& x, const int& y) override;
	bool isFocus{ false };
private:

};