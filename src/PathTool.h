#pragma once
#include "ControlBase.h"

class PathTool:public ControlBase
{
public:
	PathTool(WindowMain* root);
	~PathTool();

private:
	void resize(const int& w, const int& h);
};

