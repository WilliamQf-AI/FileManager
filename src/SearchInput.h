#pragma once
#include "ControlBase.h"

class SearchInput :public ControlBase
{
public:
	SearchInput(WindowMain* root);
	~SearchInput();

private:
	void resize(const int& w, const int& h);
};

