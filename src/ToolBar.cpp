#include "ToolBar.h"
#include "WindowMain.h"

ToolBar::ToolBar()
{
	YGNodeStyleSetWidthAuto(layout);
	YGNodeStyleSetHeight(layout, 50.f);
}

ToolBar::~ToolBar()
{
}
