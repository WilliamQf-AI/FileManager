#include "TitleBar.h"
#include "WindowMain.h"

TitleBar::TitleBar()
{
	YGNodeStyleSetWidthAuto(layout);
	YGNodeStyleSetHeight(layout, 50.f);
}

TitleBar::~TitleBar()
{
}
