#include "ToolBar.h"
#include "WindowMain.h"

ToolBar::ToolBar(WindowBase* root) :ControlBase(root)
{
	YGNodeStyleSetWidthAuto(layout);
	YGNodeStyleSetHeight(layout, 50.f);
}

ToolBar::~ToolBar()
{
}
