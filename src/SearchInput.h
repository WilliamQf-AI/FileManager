#pragma once
#include "ControlBase.h"

class SearchInput :public ControlBase
{
public:
	SearchInput(WindowMain* root);
	~SearchInput();

private:
	void resize(const int& w, const int& h);
	void paint(SkCanvas* canvas) override;
	void mouseMove(const int& x, const int& y);
	void mouseDown(const int& x, const int& y);
	int hoverIndex{ -1 };
};

