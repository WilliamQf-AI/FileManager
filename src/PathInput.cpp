#include "PathInput.h"
#include "WindowMain.h"

PathInput::PathInput(WindowMain* root) : ControlBase(root)
{
	root->resizeHandlers.push_back(
		std::bind(&PathInput::resize, this, std::placeholders::_1, std::placeholders::_2)
	);
}

PathInput::~PathInput()
{
}

void PathInput::resize(const int& w, const int& h)
{
}
