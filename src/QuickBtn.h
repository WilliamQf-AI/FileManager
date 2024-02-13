#pragma once
#include "ControlBase.h"
#include "include/core/SkCanvas.h"
class WindowMain;
class QuickBtn : public ControlBase
{
public:
	QuickBtn(WindowMain* root);
	~QuickBtn();
	void paint(SkCanvas* canvas) override;
private:
	void resize(const int& w, const int& h);
	void mouseMove(const int& x, const int& y);
	void mouseDown(const int& x, const int& y);
	int hoverIndex{ -1 };
};