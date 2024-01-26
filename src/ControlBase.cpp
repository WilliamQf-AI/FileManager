#include "ControlBase.h"
#include "WindowMain.h"

ControlBase::ControlBase() :layout{ YGNodeNew() }
{
}

ControlBase::~ControlBase()
{
}

void ControlBase::init(WindowMain* win)
{
	this->win = win;
	auto index = YGNodeGetChildCount(win->layout);
	YGNodeInsertChild(win->layout, layout,  index);
}
