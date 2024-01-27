#include "TitleBar.h"
#include "WindowMain.h"

ContentPanel::ContentPanel()
{
	YGNodeStyleSetFlexGrow(layout, 1.f);
	YGNodeStyleSetHeightAuto(layout);
}

ContentPanel::~ContentPanel()
{
}
