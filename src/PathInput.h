#pragma once
#include "ControlBase.h"

class PathInput:public ControlBase
{
public:
	PathInput(WindowMain* root);
	~PathInput();
private:
	void resize(const int& w, const int& h) override;
	void paint(SkCanvas* canvas) override;
	void mouseDown(const int& x, const int& y) override;
};

