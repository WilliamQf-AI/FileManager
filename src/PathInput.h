#pragma once
#include "ControlBase.h"

class PathInput:public ControlBase
{
public:
	PathInput(WindowMain* root);
	~PathInput();

private:
	void resize(const int& w, const int& h);
	void paint(SkCanvas* canvas) override;
	void mouseMove(const int& x, const int& y);
	void mouseDown(const int& x, const int& y);
	int hoverIndex{ -1 };
};

