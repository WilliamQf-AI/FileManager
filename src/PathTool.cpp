#include "PathTool.h"
#include "WindowMain.h"

PathTool::PathTool(WindowMain* root) : ControlBase(root)
{
	root->resizeHandlers.push_back(
		std::bind(&PathTool::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
}

PathTool::~PathTool()
{
}

void PathTool::resize(const int& w, const int& h)
{
}
